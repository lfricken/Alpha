#include "Thruster.hpp"
#include "globals.hpp"

Thruster::Thruster(const ThrusterData& rData) : GModule(rData), m_turbine(rData.turbineData)
{
    m_energyConsumption = rData.energyConsumption;
    m_force = rData.force;
    m_torque = rData.torque;
}
Thruster::~Thruster()
{

}
void Thruster::thrust(const b2Vec2& direction)//apply a force in that direction = m_force
{
    float angle = m_pBody->GetAngle();
    b2Vec2 norm;
    norm.x = cos(-angle)*direction.x + sin(-angle)*direction.y;//negative because THAT IS CORRECT, go lookup the equation!
    norm.y = -sin(-angle)*direction.x + cos(-angle)*direction.y;

    if(m_isEnabled && m_pChunk->getEnergyPool().canConsume(m_energyConsumption*game.getGameUniverse().getPhysTimeStep()))
    {
        m_pChunk->getEnergyPool().changeValue(-m_energyConsumption*game.getGameUniverse().getPhysTimeStep());

        if(getAnimationController().getState() != "Activated")
            getAnimationController().setState("Activated");
        norm.Normalize();
        m_pBody->ApplyForceToCenter(m_force*norm, true);
        m_turbine.spinup();
    }
}
void Thruster::torque(bool isCCW)//if true, rotate counter clockwise
{
    if(m_isEnabled && m_pChunk->getEnergyPool().canConsume(m_energyConsumption*game.getGameUniverse().getPhysTimeStep()))
    {
        m_pChunk->getEnergyPool().changeValue(-m_energyConsumption*game.getGameUniverse().getPhysTimeStep());

        if(getAnimationController().getState() != "Activated")
            getAnimationController().setState("Activated");
        int direction;
        if(isCCW)
            direction = 1;
        else
            direction = -1;

        m_pBody->ApplyTorque(m_torque*direction, true);
        m_turbine.spinup();
    }
}
bool Thruster::physUpdate()
{
    m_turbine.setPosition(getCenter());
    m_turbine.setVelocity(m_pBody->GetLinearVelocity());
    m_turbine.setRotation(m_pBody->GetAngle());

    return GModule::physUpdate();
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
