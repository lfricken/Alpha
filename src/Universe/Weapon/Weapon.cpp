#include "Weapon.hpp"
#include "Turret.hpp"
#include "Convert.hpp"
#include "Intelligence.hpp"

Weapon::Weapon(const WeaponData& rData) : m_linker(this), m_magazine(rData.magazine)
{
    m_energyConsumption = rData.energyConsumption;
    m_ammoConsumption = rData.ammoConsumption;
    m_ammoType = rData.ammoType;
    //magazine is auto called

    m_aimAngle = 0;//IF WE DONT do this, the turrets dont appear initially sometimes because of nan (WTF?)
    m_magazine = rData.magazine;
    m_refireTimer.setCountDown(rData.refireDelay);
    m_canPivot = rData.canPivot;
    m_startAngle = leon::degToRad(rData.startAngle);
    m_spGunMantle.reset(new Decoration(rData.decorationData));

    m_primaryFireCommands = rData.primeCommandList;
    m_secondaryFireCommands = rData.secondaryCommandList;

    for(auto it = rData.barrelData.cbegin(); it != rData.barrelData.cend(); ++it)
        m_barrels.push_back(std::tr1::shared_ptr<WeaponBarrel>( (*it)->generate(this) ));
}
Weapon::~Weapon()
{

}
void Weapon::primary(const b2Vec2& coords)
{
    aim(m_linker.getTargetPtr()->getCenter(), coords);

    EnergyPool& rEnergyPool = m_linker.getTargetPtr()->getChunk()->getEnergyPool();
    AmmoPool& rAmmoPool = m_linker.getTargetPtr()->getChunk()->getAmmoPool();

    if(m_refireTimer.isTimeUp() and (m_magazine.canConsume(m_ammoConsumption)) and (rEnergyPool.canConsume(m_energyConsumption)))
    {
        m_spGunMantle->setAnimState("Activated");
        rEnergyPool.consume(m_energyConsumption);
        m_magazine.consume(m_ammoConsumption);
        m_refireTimer.restartCountDown();
        f_queuePrimaryCommands();
        std::cout << "\n" << m_magazine.getRemainingAmmo() << ":" << m_magazine.getCapacity();
    }
    else if(not m_magazine.hasEnoughAmmo(m_ammoConsumption))
        m_magazine.reload(rAmmoPool, m_ammoType);
}
void Weapon::secondary(const b2Vec2& coords)
{
    aim(m_linker.getTargetPtr()->getCenter(), coords);

    EnergyPool& rEnergyPool = m_linker.getTargetPtr()->getChunk()->getEnergyPool();
    AmmoPool& rAmmoPool = m_linker.getTargetPtr()->getChunk()->getAmmoPool();

    if(m_refireTimer.isTimeUp() and (m_magazine.canConsume(m_ammoConsumption)) and (rEnergyPool.canConsume(m_energyConsumption)))
    {
        m_spGunMantle->setAnimState("Activated");
        rEnergyPool.consume(m_energyConsumption);
        m_magazine.consume(m_ammoConsumption);
        m_refireTimer.restartCountDown();
        f_queueSecondaryCommands();
        std::cout << "\n" << m_magazine.getRemainingAmmo() << ":" << m_magazine.getCapacity();
    }
    else if(not m_magazine.hasEnoughAmmo(m_ammoConsumption))
        m_magazine.reload(rAmmoPool, m_ammoType);
}
void Weapon::aim(const b2Vec2& rOurPos, const b2Vec2& targetPos)
{
    if(m_canPivot)//if we can aim anywhere
    {
        b2Vec2 difference(targetPos - rOurPos);
        if(difference.x >= 0)
            m_aimAngle = atan(difference.y/difference.x);
        else
            m_aimAngle = pi+atan(difference.y/difference.x);
    }
    //else
    //   m_aimAngle = m_startAngle + m_linker.getTargetPtr()->getBody()->GetAngle();
}
float Weapon::getAimAngle() const//radians
{
    if(m_canPivot)
        return m_aimAngle;
    else
        return m_startAngle + m_linker.getTargetPtr()->getBody()->GetAngle();
}
void Weapon::f_queuePrimaryCommands()
{
    m_queuedCommands.insert(m_queuedCommands.end(), m_primaryFireCommands.begin(), m_primaryFireCommands.end());//append new instructions
}
void Weapon::f_queueSecondaryCommands()
{
    m_queuedCommands.insert(m_queuedCommands.end(), m_secondaryFireCommands.begin(), m_secondaryFireCommands.end());//append new instructions
}
bool Weapon::checkFireState()
{
    //and then check if we should fire any of our barrels
    for(unsigned int i = 0; i<m_queuedCommands.size(); ++i)
    {
        m_queuedCommands[i].delay -= m_commandTimer.getTimeElapsed();
        if(m_queuedCommands[i].delay <= 0)
        {
            if(m_queuedCommands[i].barrelIndex < m_barrels.size())
            {
                m_barrels[m_queuedCommands[i].barrelIndex]->fire();
                m_queuedCommands.erase(m_queuedCommands.begin() + i);
                --i;
            }
            else
            {
                std::cout << FILELINE;
                ///ERROR LOG
            }
        }
    }
    return true;
}
void Weapon::updatePosition(const b2Vec2& rOurPos)    //update us to aim at the correct angle before trying to fire anything
{
    if(not m_canPivot)
        m_aimAngle = m_startAngle + m_linker.getTargetPtr()->getBody()->GetAngle();

    m_spGunMantle->setPosition(rOurPos);
    m_spGunMantle->setRotation(m_aimAngle);

    for(auto it = m_barrels.begin(); it != m_barrels.end(); ++it)
        (*it)->update(rOurPos, m_aimAngle);
}
void Weapon::updateVelocity(const b2Vec2& rVel)
{
    m_spGunMantle->setVelocity(rVel);
    for(auto it = m_barrels.begin(); it != m_barrels.end(); ++it)
        (*it)->updateVelocity(rVel);
}
Link<Weapon, Turret>& Weapon::getLinker()
{
    return m_linker;
}
