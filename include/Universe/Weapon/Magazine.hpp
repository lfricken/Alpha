#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "Timer.hpp"
#include "VariableNames.hpp"
#include "AmmoGroup.hpp"
#include "AmmoType.hpp"

class Magazine
{
public:
    Magazine(float reloadTime);
    virtual ~Magazine();

    void setCapacity(T_Ammo capacity);
    void setReloadTime(float time);

    T_Ammo getRemainingAmmo() const;
    T_Ammo getCapacity() const;

    void consume(T_Ammo amount);
    bool reload(AmmoGroup& rAmmoPool, AmmoType ammoType);

    bool canConsume(T_Ammo rounds) const;
    bool hasEnoughAmmo(T_Ammo rounds) const;
    bool isReloading() const;

protected:
private:
    AmmoPool m_ammo;
    Timer m_reloadTimer;
};

#endif // MAGAZINE_H
