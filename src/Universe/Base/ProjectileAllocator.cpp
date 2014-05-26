#include "ProjectileAllocator.h"

using namespace std;

ProjectileAllocator::ProjectileAllocator()
{
    //f_initialize(NULL);
}
ProjectileAllocator::ProjectileAllocator(BedFinder* pBedFinder)
{
    f_initialize(pBedFinder);
}
ProjectileAllocator::~ProjectileAllocator()
{
}
void ProjectileAllocator::f_initialize(BedFinder* pBedFinder)
{
    m_pBedFinder = pBedFinder;
    ///set up some amount of each projectile type
}
void ProjectileAllocator::add(ProjectileType type)/**make a new projectile of the specified type**/
{

}
Projectile* ProjectileAllocator::getProjectile(ProjectileType type)
{
    /**check if we have one available**/
    if(get<0>(m_projList[type]).empty())/**if not, create AT LEAST one, give a pointer to it to both lists**/
    {
        ///how many should we create if we start running out???

    }
    /**either way, pop the smart pointer from our list, and return a pointer to it**/
    m_pTemp = get<0>(m_projList[type]).back();
    get<0>(m_projList[type]).pop_back();
    return m_pTemp;
}
void ProjectileAllocator::recieveProjectile(Projectile* pSleepy)
{
    pSleepy->sleep();
    get<0>(m_projList[pSleepy->getProjType()]).push_back(pSleepy);
}
void ProjectileAllocator::load()///load definitions of projectile types from a file
{
    ///until we actually have the technology to load from a file, just do this...
    m_d
}
void ProjectileAllocator::draw()
{
    it_groupEnd = m_projList.end();
    for(it_group = m_projList.begin(); it_group != it_groupEnd; ++it_group)
    {
        it_activeEnd = get<0>(*it_group).end();

        for(it_active = get<0>(*it_group).begin(); it_active != it_activeEnd; ++it_active)
            (**it_active).draw();
    }
}
