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
    m_ammo.setMaxCapacity(capacity);
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
    m_ammo.consume(amount);
}
bool Magazine::reload(AmmoPool& rAmmoPool, AmmoType ammoType)
{
    std::cout << "\nReloading...";
    Ammo& rAmmoInPool = rAmmoPool.getAmmo(ammoType);

    if(rAmmoInPool.canConsume(m_ammo.getMaxValue() - m_ammo.getValue()))//our pool had enough ammo
    {
        rAmmoInPool.consume(m_ammo.getMaxValue() - m_ammo.getValue());
        m_ammo.add(m_ammo.getMaxValue() - m_ammo.getValue());
    }
    else
    {
        m_ammo.add(rAmmoInPool.getValue());
        rAmmoInPool.consume(rAmmoInPool.getValue());
    }
    std::cout << "\nAmmo remaining in pool: " << rAmmoInPool.getValue();
    std::cout << "\nAmmo in magazine: " << m_ammo.getValue();

    m_reloadTimer.restartCountDown();
}


bool Magazine::canConsume(T_Ammo rounds) const
{
    return (hasEnoughAmmo(rounds) && (!isReloading()));
}
bool Magazine::hasEnoughAmmo(T_Ammo rounds) const
{
    return (m_ammo.getValue() >= rounds);
}
bool Magazine::isReloading() const
{
    return !m_reloadTimer.isTimeUp();
}
