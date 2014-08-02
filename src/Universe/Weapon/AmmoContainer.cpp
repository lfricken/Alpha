#include "AmmoContainer.hpp"

AmmoContainer::AmmoContainer()
{
    m_isReloading = false;
}
AmmoContainer::~AmmoContainer()
{

}
bool AmmoContainer::isReloading() const
{
    return m_isReloading;
}
