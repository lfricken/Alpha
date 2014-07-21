#include "PhysicsBase.h"
#include "globals.h"
#include "Rotate.h"

using namespace std;

PhysicsBase::PhysicsBase() : IOBase(), m_rPhysWorld(game.getGameUniverse().getWorld())
{
    PhysicsBaseData data;
    f_initialize(data);
}
PhysicsBase::PhysicsBase(const PhysicsBaseData& data) : IOBase(static_cast<IOBaseData>(data)), m_rPhysWorld(game.getGameUniverse().getWorld())
{
    f_initialize(data);
}
void PhysicsBase::f_initialize(const PhysicsBaseData& data)
{
    if (data.shape == Shape::BOX)
    {
        m_spShape = std::tr1::shared_ptr<b2Shape>(new b2PolygonShape);
        std::tr1::static_pointer_cast<b2PolygonShape>(m_spShape)->SetAsBox(data.halfSize.x, data.halfSize.y, data.offset, leon::degToRad(data.rotation));//set our shape
        m_halfSize = data.halfSize;
    }
    else if((data.shape == Shape::OCTAGON) && (data.halfSize.x < data.halfSize.y))
    {
        m_spShape = std::tr1::shared_ptr<b2Shape>(new b2PolygonShape);
        unsigned int num = 8;
        float x = data.halfSize.x, y = data.halfSize.y;
        b2Vec2 vertices[num];

        vertices[0].Set(-x/2, y);//define CCW, starting with top left, get topmost first, then leftmost
        vertices[1].Set(-x, y-x/2);
        vertices[2].Set(-x, -y+x/2);
        vertices[3].Set(-x/2, -y);
        vertices[4].Set(x/2, -y);
        vertices[5].Set(x, -y+x/2);
        vertices[6].Set(x, y-x/2);
        vertices[7].Set(x/2, y);

        VertexData<b2Vec2> vdat = FindCenter(vertices, num);
        RotateCoordinatesDegs(vertices, num, data.rotation, vdat.center);///MAYBE WE SHOULD JUST SAY THAT 0,0 IS CENTER, instead of finding it???
        for(unsigned int i = 0; i < num; ++i)
        {
            vertices[i] -= vdat.center;//takes care of halfsize modification
            vertices[i] += data.offset;
        }
        m_halfSize = vdat.halfSize;
        std::tr1::static_pointer_cast<b2PolygonShape>(m_spShape)->Set(vertices, num);
    }
    else if((data.shape == Shape::OCTAGON) && (data.halfSize.x >= data.halfSize.y))
    {
        m_spShape = std::tr1::shared_ptr<b2Shape>(new b2PolygonShape);
        unsigned int num = 8;
        float x = data.halfSize.x, y = data.halfSize.y;
        b2Vec2 vertices[num];

        vertices[0].Set(-x/2, y);//define CCW, starting with top left, get topmost first, then leftmost
        vertices[1].Set(-x, y/2);
        vertices[2].Set(-x, -y/2);
        vertices[3].Set(-x/2, -y);
        vertices[4].Set(x/2, -y);
        vertices[5].Set(x, -y/2);
        vertices[6].Set(x, y/2);
        vertices[7].Set(x/2, y);

        VertexData<b2Vec2> vdat = FindCenter(vertices, num);
        RotateCoordinatesDegs(vertices, num, data.rotation, vdat.center);///MAYBE WE SHOULD JUST SAY THAT 0,0 IS CENTER, instead of finding it???
        for(unsigned int i = 0; i < num; ++i)
        {
            vertices[i] -= vdat.center;//takes care of halfsize modification
            vertices[i] += data.offset;
        }
        m_halfSize = vdat.halfSize;
        std::tr1::static_pointer_cast<b2PolygonShape>(m_spShape)->Set(vertices, num);
    }
    else if(data.shape == Shape::TRIANGLE)
    {
        m_spShape = std::tr1::shared_ptr<b2Shape>(new b2PolygonShape);
        unsigned int num = 3;
        float x = data.halfSize.x;
        float y = data.halfSize.y;
        b2Vec2 vertices[num];

        vertices[0].Set(0-data.halfSize.x, 0-data.halfSize.y);//define CCW, starting at right angle, then go left, then go up and left
        vertices[1].Set(2*x-data.halfSize.x, 0-data.halfSize.y);// *2 because halfsize
        vertices[2].Set(0-data.halfSize.x, 2*y-data.halfSize.y);// *2 because halfsize

        VertexData<b2Vec2> vdat = FindCenter(vertices, num);
        RotateCoordinatesDegs(vertices, num, data.rotation, vdat.center);///MAYBE WE SHOULD JUST SAY THAT 0,0 IS CENTER, instead of finding it???
        for(unsigned int i = 0; i < num; ++i)
        {
            vertices[i] -= vdat.center;//takes care of halfsize modification
            vertices[i] += data.offset;
        }
        m_halfSize = vdat.halfSize;
        std::tr1::static_pointer_cast<b2PolygonShape>(m_spShape)->Set(vertices, num);
    }
    else if(data.shape == Shape::CIRCLE)
    {
        m_spShape = std::tr1::shared_ptr<b2Shape>(new b2CircleShape);
        b2CircleShape* temp = &*std::tr1::static_pointer_cast<b2CircleShape>(m_spShape);
        temp->m_p.Set(data.offset.x, data.offset.y);//assumed to set the center
        temp->m_radius = data.halfSize.x;
        m_halfSize.x = data.halfSize.x;
        m_halfSize.y = data.halfSize.x;
    }
    else if((data.shape == Shape::POLYGON) && (data.vertices.size() > 2))
    {
        m_spShape = std::tr1::shared_ptr<b2Shape>(new b2PolygonShape);
        unsigned int num = data.vertices.size();
        b2Vec2 vertices[num];

        for(unsigned int i = 0; i < num; ++i)
            vertices[i] = data.vertices[i];

        VertexData<b2Vec2> vdat = FindCenter(vertices, num);
        RotateCoordinatesDegs(vertices, num, data.rotation, vdat.center);///MAYBE WE SHOULD JUST SAY THAT 0,0 IS CENTER, instead of finding it???

        for(unsigned int i = 0; i < num; ++i)
        {
            vertices[i] -= vdat.center;//takes care of halfsize modification
            vertices[i] += data.offset;
        }
        m_halfSize = vdat.halfSize;
        std::tr1::static_pointer_cast<b2PolygonShape>(m_spShape)->Set(vertices, num);
    }
    else
    {
        cout << "\nType [" << data.shape << "] not found in PhysicsBase.";
        ///ERROR LOG
        m_spShape = std::tr1::shared_ptr<b2Shape>(new b2PolygonShape);
        std::tr1::static_pointer_cast<b2PolygonShape>(m_spShape)->SetAsBox(data.halfSize.x, data.halfSize.y, (data.offset+data.halfSize), leon::degToRad(data.rotation));//default
        m_halfSize = data.halfSize;
    }

    m_fixtureDef.isSensor = data.isSensor;
    m_fixtureDef.shape = &*m_spShape;//give our shape to our fixture definition
    m_fixtureDef.density = data.density;
    m_fixtureDef.friction = data.friction;
    m_fixtureDef.restitution = data.restitution;//setting our fixture data
    m_fixtureDef.filter.maskBits = static_cast<uint16>(data.maskBits);
    m_fixtureDef.filter.categoryBits = static_cast<uint16>(data.categoryBits);

    m_pBody = data.pBody;
    m_pFixture = m_pBody->CreateFixture(&m_fixtureDef);
    m_pFixture->SetUserData(this);


    b2MassData massData;/**get the mass of our fixture**/
    m_pFixture->GetShape()->ComputeMass(&massData, m_pFixture->GetDensity());
    m_mass = massData.mass;
}
PhysicsBase::~PhysicsBase()
{

}
int PhysicsBase::startContact(PhysicsBase* other)
{
    Chunk* parent = static_cast<Chunk*>(m_pBody->GetUserData());
    parent->startContact(other);

    return 0;
}
int PhysicsBase::endContact(PhysicsBase* other)
{
    Chunk* parent = static_cast<Chunk*>(m_pBody->GetUserData());
    parent->endContact(other);
    return 0;
}
int PhysicsBase::preSolveContact(PhysicsBase* other)
{
    Chunk* parent = static_cast<Chunk*>(m_pBody->GetUserData());
    parent->preSolveContact(other);
    return 0;
}
int PhysicsBase::postSolveContact(PhysicsBase* other)
{
    Chunk* parent = static_cast<Chunk*>(m_pBody->GetUserData());
    parent->postSolveContact(other);
    return 0;
}
bool PhysicsBase::physUpdate()
{
    return false;
}



b2World& PhysicsBase::getWorld()
{
    return m_rPhysWorld;
}


b2Fixture* PhysicsBase::getFixture()
{
    return m_pFixture;
}



const b2Body* PhysicsBase::getBody() const
{
    return m_pBody;
}
const b2Fixture* PhysicsBase::getFixture() const
{
    return m_pFixture;
}
float PhysicsBase::getMass() const
{
    return m_mass;
}
b2Vec2 PhysicsBase::getCenter() const
{
    b2Vec2 center(0,0);

    if(m_spShape->GetType() == b2Shape::e_polygon)
    {
        center = m_pBody->GetWorldPoint(static_cast<b2CircleShape*>(&*m_spShape)->GetVertex(0));
    }
    else if(m_spShape->GetType() == b2Shape::e_circle)//must be a circle
    {
        b2PolygonShape* pPShape = static_cast<b2PolygonShape*>(&*m_spShape);

        unsigned int num = pPShape->GetVertexCount();
        for(unsigned int i = 0; i<num; ++i)
            center += pPShape->GetVertex(i);

        center.x /= num;
        center.y /= num;
        center = m_pBody->GetWorldPoint(center);
    }
    else
    {
        std::cout << FILELINE;
        ///eRROR LOG
    }
    return center;
}
