#include "PhysicsBase.h"
#include "globals.h"

using namespace std;

PhysicsBase::PhysicsBase(PhysicsBaseData& data, IOBaseData& baseData) : IOBase(baseData), m_rPhysWorld(game.getGameUniverse().getWorld())
{
    if (data.shape == PhysicsBaseData::Box)
    {
        m_shape = new b2PolygonShape;
        static_cast<b2PolygonShape*>(m_shape)->SetAsBox(data.halfSize.x, data.halfSize.y, data.offset, data.rotation);//set our shape
    }
    else if((data.shape == PhysicsBaseData::Octagon) && (data.halfSize.x < data.halfSize.y))
    {
        m_shape = new b2PolygonShape;
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

        static_cast<b2PolygonShape*>(m_shape)->Set(vertices, num);
    }
    else if((data.shape == PhysicsBaseData::Octagon) && (data.halfSize.x >= data.halfSize.y))
    {
        m_shape = new b2PolygonShape;
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

        static_cast<b2PolygonShape*>(m_shape)->Set(vertices, num);
    }
    else if(data.shape == PhysicsBaseData::Triangle)
    {
        m_shape = new b2PolygonShape;
        int32 num = 3;
        float x = data.halfSize.x, y = data.halfSize.y;
        b2Vec2 vertices[num];

        vertices[0].Set(0, 0);//define CCW, starting at right angle, then go left, then go up and left
        vertices[1].Set(2*x, 0);// *2 because halfsize
        vertices[2].Set(0, 2*y);// *2 because halfsize
        for(int i = 0; i < num; ++i)
            vertices[i]+= data.offset;

        static_cast<b2PolygonShape*>(m_shape)->Set(vertices, num);
    }
    else if(data.shape == PhysicsBaseData::Circle)
    {
                cout << "\nCircle";
        m_shape = new b2CircleShape;
        static_cast<b2CircleShape*>(m_shape)->m_p.Set(data.offset.x, data.offset.y);
        static_cast<b2CircleShape*>(m_shape)->m_radius = data.halfSize.x;

    }
    else
    {
        m_shape = new b2PolygonShape;
        static_cast<b2PolygonShape*>(m_shape)->SetAsBox(data.halfSize.x, data.halfSize.y, data.offset, data.rotation);//default
    }

    m_fixtureDef.isSensor = data.isSensor;
    m_fixtureDef.shape = m_shape;//give our shape to our fixture definition
    m_fixtureDef.density = data.density;
    m_fixtureDef.friction = data.friction;
    m_fixtureDef.restitution = data.restitution;//setting our fixture data
    m_fixtureDef.filter.maskBits = data.maskBits;
    m_fixtureDef.filter.categoryBits = data.categoryBits;

    m_pBody = data.pBody;
    m_pFixture = m_pBody->CreateFixture(&m_fixtureDef);

}
PhysicsBase::~PhysicsBase()
{
    delete m_shape;
}
bool PhysicsBase::contact(void* other)
{
    damage(1);
    return true;///why do we return true? should we be returning anything at all?
}
bool PhysicsBase::endContact(void* other)
{
    ///end contact stuff that we do
    return true;///why do we return true? should we be returning anything at all?
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


int PhysicsBase::damage(int damage)
{
    m_health.takeDamage(damage);
    if(m_spEventer->amount() != 0)
    {
        std::ostringstream convert;   // stream used for the conversion
        convert << m_health.value;      // insert the textual representation of 'Number' in the characters in the stream
        m_spEventer->event(convert.str(), m_health.varName);
    }

    return m_health.value;
}
int PhysicsBase::getHealth() const
{
    return m_health.value;
}
