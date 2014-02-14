#include <MultipleInheritance/PhysicsBase.h>

#include <globals.h>

using namespace std;


b2World& PhysicsBase::m_rPhysWorld = game.getGameUniverse().getWorld();


PhysicsBase::PhysicsBase()// : m_rPhysWorld(rPhysWorld)
{
}
PhysicsBase::~PhysicsBase()
{

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
