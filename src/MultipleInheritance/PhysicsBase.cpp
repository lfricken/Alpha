#include "PhysicsBase.h"
#include "globals.h"

using namespace std;


b2World& PhysicsBase::m_rPhysWorld = game.getGameUniverse().getWorld();


PhysicsBase::PhysicsBase(const PhysicsBaseData& data, const IOBaseData& baseData) : IOBase(baseData)
{
    if (data.shape == PhysicsBaseData::Box)
        m_shape.SetAsBox(data.halfSize.x, data.halfSize.y, data.offset, data.rotation);//set our shape
    else if((data.shape == PhysicsBaseData::Octagon) && (data.halfSize.x < data.halfSize.y))
    {
        int32 num = 8;
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

        for(int i = 0; i < num; ++i)
            vertices[i]+= data.offset;

        m_shape.Set(vertices, num);
    }
    else if((data.shape == PhysicsBaseData::Octagon) && (data.halfSize.x >= data.halfSize.y))
    {
        int32 num = 8;
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
        for(int i = 0; i < num; ++i)
            vertices[i]+= data.offset;

        m_shape.Set(vertices, num);
    }
    else if(data.shape == PhysicsBaseData::Triangle)
    {
        int32 num = 3;
        float x = data.halfSize.x, y = data.halfSize.y;
        b2Vec2 vertices[num];

        vertices[0].Set(0, 0);//define CCW, starting at right angle, then go left, then go up and left
        vertices[1].Set(2*x, 0);// *2 because halfsize
        vertices[2].Set(0, 2*y);// *2 because halfsize
        for(int i = 0; i < num; ++i)
            vertices[i]+= data.offset;

        m_shape.Set(vertices, num);
    }
    else
        m_shape.SetAsBox(data.halfSize.x, data.halfSize.y, data.offset, data.rotation);//default


    m_fixtureDef.shape = &m_shape;//give our shape to our fixture definition
    m_fixtureDef.density = data.density;
    m_fixtureDef.friction = data.friction;
    m_fixtureDef.restitution = data.restitution;//setting our fixture data
    m_pBody = data.pBody;

    m_pFixture = m_pBody->CreateFixture(&m_fixtureDef);
}
PhysicsBase::~PhysicsBase()
{

}
bool PhysicsBase::collide(void* other)
{
    static_cast<IOBase*>(other)->damage(1);
    return true;///why do we return true? should we be returning anything at all?
}
b2World& PhysicsBase::getWorld()
{
    return m_rPhysWorld;
}


const b2PolygonShape& PhysicsBase::getShape() const
{
    return m_shape;
}
b2PolygonShape& PhysicsBase::getShape()
{
    return m_shape;
}

const b2FixtureDef& PhysicsBase::getFixtureDef() const
{
    return m_fixtureDef;
}
b2FixtureDef& PhysicsBase::getFixtureDef()
{
    return m_fixtureDef;
}


b2Fixture& PhysicsBase::getFixture() const
{
    return *m_pFixture;
}
b2Body& PhysicsBase::getBody() const
{
    return *m_pBody;
}


b2Fixture& PhysicsBase::getFixture()
{
    return *m_pFixture;
}
b2Body& PhysicsBase::getBody()
{
    return *m_pBody;
}

void PhysicsBase::setFixture(b2Fixture* pFixture)
{
    m_pFixture = pFixture;
}
void PhysicsBase::setBody(b2Body* pBody)
{
    m_pBody = pBody;
}
