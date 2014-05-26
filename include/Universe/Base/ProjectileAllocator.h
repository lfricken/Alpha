#ifndef PROJECTILEALLOCATOR_H
#define PROJECTILEALLOCATOR_H

#include "BedFinder.h"
#include "Projectile.h"
#include "Chunk.h"

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
    ProjectileAllocator(BedFinder* pBedFinder);
    virtual ~ProjectileAllocator();

    Projectile* getProjectile(ProjectileType type);
    void recieveProjectile(Projectile* pSleepy);
    void add(ProjectileType type);/**make a new projectile of the specified type**/
    void load();///load definitions from a file

    void draw();
protected:
private:
    /**first list is ready, second is permanent holder list**/
    typedef std::vector<std::tr1::shared_ptr<Projectile> > ProjSPList;
    typedef std::vector<Projectile*> ProjPList;
    typedef std::vector<std::tuple<ProjPList, ProjSPList, ProjectileData> > ProjListPairing;

    void f_initialize(BedFinder* pBedFinder);

    BedFinder* m_pBedFinder;/// WE DON'T NEED THIS, ALL CHUNKS HAVE ACCESS TO IT used to find our sleeping people a bed
    Projectile* m_pTemp;
    ProjectileData& m_data;

    ProjListPairing m_projList;//projectiles, we keep different types in different vectors

    /**used for speeding up loops, like draw**/
    ProjListPairing::iterator it_groupEnd;
    ProjListPairing::iterator it_group;
    ProjPList::iterator it_activeEnd;
    ProjPList::iterator it_active;
};

#endif // PROJECTILEALLOCATOR_H
