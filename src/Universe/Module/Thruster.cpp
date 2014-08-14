#include "Thruster.hpp"

Thruster::Thruster() : GModule()
{
    ThrusterData data;
    f_initialize(data);
}
Thruster::Thruster(const ThrusterData& data) : GModule(static_cast<GModuleData>(data))
{
    f_initialize(data);
}
Thruster::~Thruster()
{

}
void Thruster::f_initialize(const ThrusterData& data)
{
    m_force = data.force;
    m_torque = data.torque;
}
void Thruster::thrust(const b2Vec2& direction)//apply a force in that direction = m_force
{
    if(m_isEnabled)
    {
        if(getAnimationController().getState() != "Thrusting")
            getAnimationController().setState("Thrusting");
        b2Vec2 norm = direction;
        norm.Normalize();
        m_pBody->ApplyForceToCenter(m_force*norm, true);
    }
}
void Thruster::torque(bool isCCW)//if true, rotate counter clockwise
{
    if(m_isEnabled)
    {
        if(getAnimationController().getState() != "Thrusting")
            getAnimationController().setState("Thrusting");
        int direction;
        if(isCCW)
            direction = 1;
        else
            direction = -1;

        m_pBody->ApplyTorque(m_torque*direction, true);
    }
}
void Thruster::up()
{
    thrust(b2Vec2(0, 1));
}
void Thruster::down()
{
    thrust(b2Vec2(0, -1));
}
void Thruster::left()
{
    thrust(b2Vec2(-1, 0));
}
void Thruster::right()
{
    thrust(b2Vec2(1, 0));
}
void Thruster::rollLeft()
{
    torque(true);
}
void Thruster::rollRight()
{
    torque(false);
}
