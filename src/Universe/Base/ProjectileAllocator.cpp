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
    load();

}
void ProjectileAllocator::add(ProjectileType type)/**make a new projectile of the specified type**/
{
    m_GModuleDataList.clear();/**clear our GModule list**/
    m_GModuleDataList.push_back(std::tr1::shared_ptr<GModuleData>(  new GModuleData(  get<gModData>(m_projList[type]  ))    ));/**add a single element to it of the correct type from tuple**/
    Projectile* m_pProjTemp = new Projectile(get<projData>(m_projList[type]));/**create a new projectile of the correct type with the data in tuple**/
    m_pProjTemp->add(m_GModuleDataList);/**add our GModule List to it**/
    m_pProjTemp->setListPos(get<spList>(m_projList[type]).size());//since we WILL be at the end of the list    /**tell the projectile what it's index is, and increment the new value**/
    get<spList>(m_projList[type]).push_back(tr1::shared_ptr<Projectile>(m_pProjTemp));    /**finally, add the new projectile**/
}
Projectile* ProjectileAllocator::getProjectile(ProjectileType type)
{
    /**check to make sure we won't crash**/
    if(m_projList.size()-1 < type)
    {
        ///ERROR LOG
        cout << "\nRequested [" << type << "] but max was [" << m_projList.size()-1 << "].";
    }


    /**check if we have one available by comparing the free index to the size of our projectile list**/
    if(get<spList>(m_projList[type]).size() == get<freeIndex>(m_projList[type]))/**if not, create AT LEAST one**/
    {
        cout << "\nAdd();";
        add(type); ///how many should we create if we start running out??? //it will initially be sleeping
    }

    get<freeIndex>(m_projList[type]) += 1; /**either way, increase free index by 1, and give a pointer to this one**/

    return static_cast<Projectile*>(get<spList>(m_projList[type])[get<freeIndex>(m_projList[type])-1].get());
}
void ProjectileAllocator::recieveProjectile(Projectile* pSleepy)
{
    ///we can't do this during a timestep!!! mark it for later capture

    //cout << "\nProjectile Received!";
    m_recoverList.push_back(pSleepy);
}
void ProjectileAllocator::load()///load definitions of projectile types from a file
{
    /**access first type START**/
    unsigned int type = 0;
    m_projList.resize(type+1);

    get<spList>(m_projList[type]).clear();
    get<freeIndex>(m_projList[type]) = 0;

    GModuleData& data = get<gModData>(m_projList[type]);
    data.type = ClassType::GMODULE;
    data.shape = Shape::BOX;
    data.categoryBits = collide::CollisionCategory::Projectile;
    data.maskBits = collide::CollisionCategory::ShipModule | collide::CollisionCategory::Sensor;
    data.isSensor = false;
    data.density = 1.0f;
    data.friction = 0.4f;
    data.halfSize = b2Vec2(0.25, 0.25);
    data.offset = b2Vec2(0, 0);
    data.pBody = NULL;//we dont know it yet
    data.restitution = 0.2f;
    data.rotation = 0.0f;
    data.texTile = sf::Vector2f(0, 0);
    data.color = sf::Color::White;

    ProjectileData& rProjData = get<projData>(m_projList[type]);
    rProjData.projType = type;
    //do stuff
    /**access first type END**/

    ///until we actually have the technology to load from a file, just do this...
    ///m_data
}
void ProjectileAllocator::draw()
{
    int i;
    int to;
    ProjSPList* pActiveList = NULL;
    auto it_groupEnd = m_projList.end();

    for(auto it_group = m_projList.begin(); it_group != it_groupEnd; ++it_group)
    {
        pActiveList = &get<spList>(*it_group);

        to = get<freeIndex>(*it_group);
        for(i = 0; i < to; ++i)
        {
            (*pActiveList)[i]->draw();
        }
    }
}
void ProjectileAllocator::recoverProjectiles()
{
    /**for each element in here
    ,make sure it isn't already asleep
    if it isn't put it to sleep
    and re insert it to the front,
    moving the free thing backwards
    and finally, clear the recoverList for future use**/

    /**take this new pointer, find it's position, find the position of the highest (used element) (free index-1)**/
    /**set this one to sleep, swap their positions, update positions, reduce index by 1**/

    ProjSPList* pVec;

    auto it_end = m_recoverList.end();
    for(auto it = m_recoverList.begin(); it != it_end; ++it)
    {
        if((*it)->isAwake())//make sure isn't asleep
        {

            pVec = &get<spList>(m_projList[(*it)->getProjType()]);



            std::swap( (*pVec)[ (*it)->getListPos() ], (*pVec)[ get<freeIndex>(m_projList[ (*it)->getProjType() ])-1 ]);//re insert it to the front

            (*it)->swapListPos(*(*pVec)[(*it)->getListPos()]);//swap positions with what is now in our old spot

            (*it)->sleep();//set us to sleep

            get<freeIndex>(m_projList[ (*it)->getProjType() ]) -= 1;//move the free index back 1
        }
    }

    m_recoverList.clear();

    // ProjSPList& vec = get<spList>(m_projList[pSleepy->getProjType()]);
    // std::swap(vec[ pSleepy->getListPos() ], vec[ get<freeIndex>(m_projList[pSleepy->getProjType()])-1 ]);
    // pSleepy->swapListPos(*vec[pSleepy->getListPos()]);//swap positions with what is now in our old spot
    //pSleepy->sleep();
}
