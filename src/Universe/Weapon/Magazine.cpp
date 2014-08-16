#include "Magazine.hpp"

Magazine::Magazine(float reloadTime) : m_ammo(NULL, 10, 10)
{
    m_reloadTimer.setCountDown(reloadTime);
}
Magazine::~Magazine()
{

}


void Magazine::setCapacity(T_Ammo capacity)
{
    m_ammo.setMaxValue(capacity);
}
void Magazine::setReloadTime(float time)
{
    m_reloadTimer.setCountDown(time);
}



T_Ammo Magazine::getRemainingAmmo() const
{
    return m_ammo.getValue();
}
T_Ammo Magazine::getCapacity() const
{
    return m_ammo.getMaxValue();
}


void Magazine::consume(T_Ammo amount)
{
    m_ammo.changeValue(-amount);
}
bool Magazine::reload(AmmoGroup& rAmmoGroup, AmmoType ammoType)
{
    std::cout << "\nReloading...";
    AmmoPool& rAmmoPool = rAmmoGroup.getAmmo(ammoType);

    if(rAmmoPool.canConsume(m_ammo.getMaxValue() - m_ammo.getValue()))//our pool had enough ammo
    {
        rAmmoPool.changeValue(-(m_ammo.getMaxValue() - m_ammo.getValue()));
        m_ammo.changeValue(m_ammo.getMaxValue() - m_ammo.getValue());
    }
    else
    {
        m_ammo.changeValue(rAmmoPool.getValue());
        rAmmoPool.changeValue(-rAmmoPool.getValue());
    }
    std::cout << "\nAmmo remaining in pool: " << rAmmoPool.getValue() << "/" << rAmmoPool.getMaxValue();
    std::cout << "\nAmmo in magazine: " << m_ammo.getValue();

    m_reloadTimer.restartCountDown();
    return true;
}


bool Magazine::canConsume(T_Ammo rounds) const
{
    return (hasEnoughAmmo(rounds) && (!isReloading()));
}
bool Magazine::hasEnoughAmmo(T_Ammo rounds) const
{
    return (m_ammo.canConsume(rounds));
}
bool Magazine::isReloading() const
{
    return !m_reloadTimer.isTimeUp();
}
