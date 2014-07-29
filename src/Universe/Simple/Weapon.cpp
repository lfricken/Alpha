#include "Weapon.h"
#include "Turret.h"
#include "Angles.h"

Weapon::Weapon(const WeaponData& rData) : m_linker(this)
{
    m_aimAngle = 0;//IF WE DONT do this, the turrets dont appear initially sometimes because of nan (WTF?)
    m_ammoContainer = rData.ammo;
    m_refireTimer.setCountDown(rData.refireDelay);
    m_canPivot = rData.canPivot;
    m_spGunMantle.reset(new Decoration(rData.decorationData));
    m_fireCommands = rData.fireCommandList;

    std::vector<WeaponBarrelData> data = rData.barrelData;
    for(auto it = data.begin(); it != data.end(); ++it)
    {
        m_barrels.push_back(WeaponBarrel(*it, this));
    }
}
Weapon::~Weapon()
{

}
void Weapon::primary(const b2Vec2& coords)
{
    if(m_refireTimer.isTimeUp() && (!m_ammoContainer.isReloading()))
        f_queueCommands();
}
void Weapon::secondary(const b2Vec2& coords)
{
    if(m_refireTimer.isTimeUp() && (!m_ammoContainer.isReloading()))
        f_queueCommands();
}
void Weapon::aim(const b2Vec2& coords)
{
    b2Vec2 difference(coords - m_linker.getTargetPtr()->getCenter());
    if(difference.x >= 0)
        m_aimAngle = atan(difference.y/difference.x);
    else
        m_aimAngle = pi+atan(difference.y/difference.x);
}
float Weapon::getAimAngle() const//radians
{
    return m_aimAngle;
}
void Weapon::f_queueCommands()
{
    m_queuedCommands.insert(m_queuedCommands.end(), m_fireCommands.begin(), m_fireCommands.end());//append new instructions
}
bool Weapon::checkFireState()
{
    //update us to aim at the correct angle before trying to fire anything

    b2Vec2 position(m_linker.getTargetPtr()->getCenter());


    m_spGunMantle->setPosition(position);
    m_spGunMantle->setRotation(m_aimAngle);

    for(auto it = m_barrels.begin(); it != m_barrels.end(); ++it)
        it->update(position, m_aimAngle);




    //and then check if we should fire any of our barrels
    for(unsigned int i = 0; i<m_queuedCommands.size(); ++i)
    {
        m_queuedCommands[i].delay -= m_commandTimer.getTimeElapsed();
        if(m_queuedCommands[i].delay <= 0)
        {
            if(m_queuedCommands[i].barrelIndex < m_barrels.size())
            {
                m_barrels[m_queuedCommands[i].barrelIndex].fire();
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
}
Link<Weapon, Turret>& Weapon::getLinker()
{
    return m_linker;
}
