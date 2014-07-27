#include "AmmoContainer.h"

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
