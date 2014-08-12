#ifndef PROJECTILEALLOCATOR_H
#define PROJECTILEALLOCATOR_H

#include "BedFinder.hpp"
#include "Projectile.hpp"
#include "Timer.hpp"

/**we hold our own chunks**/
/**when a gun fires, it asks for a bullet from us through universe**/
/**we give a pointer to our bullet and let them do the rest**/
/**when the bullet has determined it's lifetime is up, it passes us a pointer to itself, and we put it to sleep from coords given by bed finder**/
/**put a pointer to it into the first list**/
/**meanwhile we keep a pointer to every bullet, and a pointer those that are free**/
class ProjectileAllocator
{
public:
    ProjectileAllocator();
    virtual ~ProjectileAllocator();

    Projectile* getProjectile(ProjectileType type);
    void recieveProjectile(Projectile* pSleepy);
    void add(ProjectileType type);/**make a new projectile of the specified type**/
    void load();///load projectile definitions from a file

    void recoverProjectiles();//take our list of projectile* and re insert them
    void gfxUpdate();
protected:
private:
    void f_initialize();

    /**first list is ready, second is permanent holder list**/
    typedef std::vector<std::tr1::shared_ptr<Projectile> > ProjSPList;
    typedef std::vector<std::tuple<ProjSPList, unsigned int, GModuleData, ProjectileData> > ProjListPairing;
    enum{spList = 0, freeIndex = 1, gModData = 2, projData = 3,};

    std::vector<Projectile*> m_recoverList;
    ProjListPairing m_projList;//projectiles + other stuff, we keep different types in different tuples

    Timer m_timer;
};

#endif // PROJECTILEALLOCATOR_H
