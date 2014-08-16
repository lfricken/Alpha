#include "AmmoGroup.hpp"

AmmoGroup::AmmoGroup()
{

}
AmmoGroup::~AmmoGroup()
{

}
AmmoPool& AmmoGroup::getAmmo(AmmoType key)
{
    return m_ammos[key];
}
