#include "AmmoPool.hpp"

AmmoPool::AmmoPool()
{

}
AmmoPool::~AmmoPool()
{

}
Ammo& AmmoPool::getAmmo(AmmoType key)
{
    return m_ammos[key];
}
