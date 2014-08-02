#ifndef AMMOPOOL_H
#define AMMOPOOL_H

#include "VariableNames.hpp"
#include "AmmoType.hpp"

class AmmoPool
{
public:
    AmmoPool();
    virtual ~AmmoPool();

    Ammo& getAmmo(AmmoType key);
protected:
private:
    std::map<AmmoType, Ammo> m_ammos;
};

#endif // AMMOPOOL_H
