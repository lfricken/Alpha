#include "PhysicsBase.h"
#include "globals.h"
#include "Rotate.h"

using namespace std;

PhysicsBase::PhysicsBase() :
    IOBase(),
    m_rPhysWorld(game.getGameUniverse().getWorld())
{
    PhysicsBaseData data;
    f_initialize(data);
}
PhysicsBase::PhysicsBase(const PhysicsBaseData& data) :
    IOBase(static_cast<IOBaseData>(data)),
    m_rPhysWorld(game.getGameUniverse().getWorld())
{
    f_initialize(data);
}
void PhysicsBase::f_initialize(const PhysicsBaseData& data)
{
    //if(!data.vertices.empty())//if we have some vertex data, use it
   // {
   //     vector<b2Vec2> vertices = data.vertices;
    //    RotateCoordinatesDegs(vertices, data.rotation, FindCenter(vertices));/**we want to rotate about center because otherwise, strange things will happen**////MAYBE WE SHOULD JUST SAY THAT 0,0 IS CENTER, instead of finding it???
   // }
    if (data.shape == Shape::BOX)
    {
        m_shape = std::tr1::shared_ptr<b2Shape>(new b2PolygonShape);
        std::tr1::static_pointer_cast<b2PolygonShape>(m_shape)->SetAsBox(data.halfSize.x, data.halfSize.y, data.offset, leon::degToRad(data.rotation));//set our shape
    }
    else if((data.shape == Shape::OCTAGON) && (data.halfSize.x < data.halfSize.y))
    {
        m_shape = std::tr1::shared_ptr<b2Shape>(new b2PolygonShape);
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

        RotateCoordinatesDegs(vertices, num, data.rotation, FindCenter(vertices, num));///MAYBE WE SHOULD JUST SAY THAT 0,0 IS CENTER, instead of finding it???
        for(unsigned int i = 0; i < num; ++i)
        {
            vertices[i] += data.offset;
        }

        std::tr1::static_pointer_cast<b2PolygonShape>(m_shape)->Set(vertices, num);
    }
    else if((data.shape == Shape::OCTAGON) && (data.halfSize.x >= data.halfSize.y))
    {
        m_shape = std::tr1::shared_ptr<b2Shape>(new b2PolygonShape);
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

        RotateCoordinatesDegs(vertices, num, data.rotation, FindCenter(vertices, num));///MAYBE WE SHOULD JUST SAY THAT 0,0 IS CENTER, instead of finding it???
        for(unsigned int i = 0; i < num; ++i)
        {
            vertices[i] += data.offset;
        }

        std::tr1::static_pointer_cast<b2PolygonShape>(m_shape)->Set(vertices, num);
    }
    else if(data.shape == Shape::TRIANGLE)
    {
        m_shape = std::tr1::shared_ptr<b2Shape>(new b2PolygonShape);
        unsigned int num = 3;
        float x = data.halfSize.x;
        float y = data.halfSize.y;
        b2Vec2 vertices[num];

        vertices[0].Set(0-data.halfSize.x, 0-data.halfSize.y);//define CCW, starting at right angle, then go left, then go up and left
        vertices[1].Set(2*x-data.halfSize.x, 0-data.halfSize.y);// *2 because halfsize
        vertices[2].Set(0-data.halfSize.x, 2*y-data.halfSize.y);// *2 because halfsize

        RotateCoordinatesDegs(vertices, num, data.rotation, FindCenter(vertices, num));///MAYBE WE SHOULD JUST SAY THAT 0,0 IS CENTER, instead of finding it???
        for(unsigned int i = 0; i < num; ++i)
        {
            vertices[i] += data.offset;
        }

        std::tr1::static_pointer_cast<b2PolygonShape>(m_shape)->Set(vertices, num);
    }
    else if(data.shape == Shape::CIRCLE)
    {
        m_shape = std::tr1::shared_ptr<b2Shape>(new b2CircleShape);
        b2CircleShape* temp = &*std::tr1::static_pointer_cast<b2CircleShape>(m_shape);
        temp->m_p.Set(data.offset.x, data.offset.y);
        temp->m_radius = data.halfSize.x;
    }
    else if((data.shape == Shape::POLYGON) && (data.vertices.size() > 2))
    {
        m_shape = std::tr1::shared_ptr<b2Shape>(new b2PolygonShape);
        unsigned int num = data.vertices.size();
        b2Vec2 vertices[num];

        for(unsigned int i = 0; i < num; ++i)
            vertices[i] = data.vertices[i];

        RotateCoordinatesDegs(vertices, num, data.rotation, FindCenter(vertices, num));///MAYBE WE SHOULD JUST SAY THAT 0,0 IS CENTER, instead of finding it???

        for(unsigned int i = 0; i < num; ++i)
            vertices[i] += data.offset;

        std::tr1::static_pointer_cast<b2PolygonShape>(m_shape)->Set(vertices, num);
    }
    else
    {
        cout << "\nType [" << data.shape << "] not found in PhysicsBase.";
        ///ERROR LOG
        m_shape = std::tr1::shared_ptr<b2Shape>(new b2PolygonShape);
        std::tr1::static_pointer_cast<b2PolygonShape>(m_shape)->SetAsBox(data.halfSize.x, data.halfSize.y, data.offset, leon::degToRad(data.rotation));//default
    }

    m_fixtureDef.isSensor = data.isSensor;
    m_fixtureDef.shape = m_shape.get();//give our shape to our fixture definition
    m_fixtureDef.density = data.density;
    m_fixtureDef.friction = data.friction;
    m_fixtureDef.restitution = data.restitution;//setting our fixture data
    m_fixtureDef.filter.maskBits = static_cast<uint16>(data.maskBits);
    m_fixtureDef.filter.categoryBits = static_cast<uint16>(data.categoryBits);

    m_pBody = data.pBody;
    m_pFixture = m_pBody->CreateFixture(&m_fixtureDef);
    m_pFixture->SetUserData(this);
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
const b2Shape& PhysicsBase::getShape() const
{
    return *m_shape;
}
b2Shape& PhysicsBase::getShape()
{
    return *m_shape;
}

const b2FixtureDef& PhysicsBase::getFixtureDef() const
{
    return m_fixtureDef;
}
b2FixtureDef& PhysicsBase::getFixtureDef()
{
    return m_fixtureDef;
}


b2Fixture* PhysicsBase::getFixture() const
{
    return m_pFixture;
}
b2Body* PhysicsBase::getBody() const
{
    return m_pBody;
}


b2Fixture* PhysicsBase::getFixture()
{
    return m_pFixture;
}
b2Body* PhysicsBase::getBody()
{
    return m_pBody;
}

void PhysicsBase::setFixture(b2Fixture* pFixture)
{
    m_pFixture = pFixture;
}
void PhysicsBase::setBody(b2Body* pBody)
{
    m_pBody = pBody;
}

///just for testing purposes
int PhysicsBase::damage(int damage)
{
    m_health.takeDamage(damage);

    std::ostringstream convert;   // stream used for the conversion
    convert << m_health.getValue();      // insert the textual representation of 'Number' in the characters in the stream
    m_spEventer->event(convert.str(), m_health.getEventType());

    return m_health.getValue();
}
int PhysicsBase::getHealth() const
{
    return m_health.getValue();
}
