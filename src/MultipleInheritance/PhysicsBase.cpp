#include <MultipleInheritance/PhysicsBase.h>

#include <globals.h>

using namespace std;


b2World& PhysicsBase::m_rPhysWorld = game.getGameUniverse().getWorld();


PhysicsBase::PhysicsBase(PhysicsBaseData& data)// : m_rPhysWorld(rPhysWorld)
{
    m_shape.SetAsBox(data.halfSize.x, data.halfSize.y, data.offset, data.rotation);//set our shape

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
bool PhysicsBase::physicsInput(Package& rPackage)
{
    return false;
}
bool PhysicsBase::collide(void* other)
{
    Package message;
    message.commandType = GRAPHICS;
    message.command = "IncTexTile";
    static_cast<IOBase*>(other)->input(message);
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
