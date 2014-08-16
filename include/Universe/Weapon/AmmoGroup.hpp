#ifndef AMMOGROUP_H
#define AMMOGROUP_H

#include "VariableNames.hpp"
#include "AmmoType.hpp"

class AmmoGroup
{
public:
    AmmoGroup();
    virtual ~AmmoGroup();

    AmmoPool& getAmmo(AmmoType key);
protected:
private:
    std::map<AmmoType, AmmoPool> m_ammos;
};

#endif // AMMOGROUP_H
