#include "ProjectileAllocator.hpp"

#include "GModule.hpp"

using namespace std;

ProjectileAllocator::ProjectileAllocator()
{
    f_initialize();
}
ProjectileAllocator::~ProjectileAllocator()
{

}
void ProjectileAllocator::f_initialize()
{
    load();

}
void ProjectileAllocator::add(ProjectileType type)/**make a new projectile of the specified type**/
{
    std::vector<std::tr1::shared_ptr<const GModuleData> > gModuleDataList;
    gModuleDataList.push_back(std::tr1::shared_ptr<const GModuleData>(  new GModuleData(  get<gModData>(m_projList[type]  ))    ));/**add a single element to it of the correct type from tuple**/
    Projectile* m_pProjTemp = new Projectile(get<projData>(m_projList[type]));/**create a new projectile of the correct type with the data in tuple**/
    m_pProjTemp->add(gModuleDataList);/**add our GModule List to it**/
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
        add(type); ///how many should we create if we start running out???
    }

    get<freeIndex>(m_projList[type]) += 1; /**either way, increase free index by 1, and give a pointer to this one**/

    return (get<spList>(m_projList[type])[get<freeIndex>(m_projList[type])-1].get());
}
void ProjectileAllocator::recieveProjectile(Projectile* pSleepy)
{
    //we can't do this during a timestep!!! mark it for later capture
    //cout << "\nProjectile Received!";
    m_recoverList.push_back(pSleepy);
}
void ProjectileAllocator::load()///load definitions of projectile types from a file
{
    /**access first type START**/
    GModuleData* data;
    ProjectileData* rProjData;
    unsigned int type;
    m_projList.resize(2);



    type = 0;

    get<spList>(m_projList[type]).clear();
    get<freeIndex>(m_projList[type]) = 0;

    data = &get<gModData>(m_projList[type]);
    (*data).type = ClassType::GMODULE;
    (*data).shape = Shape::CIRCLE;
    (*data).texName = "textures/bullet_white_32.png";
    (*data).categoryBits = Category::Projectile;
    (*data).maskBits = Mask::ProjectileOff;
    (*data).isSensor = false;
    (*data).density = 0.1f;
    (*data).friction = 0.4f;
    (*data).halfSize = b2Vec2(0.0625, 0.0625);
    (*data).offset = b2Vec2(0, 0);
    (*data).pBody = NULL;//we dont know it yet
    (*data).restitution = 0.2f;
    (*data).rotation = 0.0f;
    (*data).texTileSize = sf::Vector2f(32, 32);
    (*data).color = sf::Color::White;

    rProjData = &get<projData>(m_projList[type]);
    (*rProjData).projType = type;
    (*rProjData).damage = T_Damage(100, 500);
    //do stuff
    /**access first type END**/

    type = 1;

    get<spList>(m_projList[type]).clear();
    get<freeIndex>(m_projList[type]) = 0;

    data = &get<gModData>(m_projList[type]);
    (*data).type = ClassType::GMODULE;
    (*data).shape = Shape::CIRCLE;
    (*data).texName = "textures/bullet_green_64.png";
    (*data).categoryBits = Category::Projectile;
    (*data).maskBits = Mask::ProjectileOff;
    (*data).isSensor = false;
    (*data).density = 0.1f;
    (*data).friction = 0.4f;
    (*data).halfSize = b2Vec2(0.125, 0.125);
    (*data).offset = b2Vec2(0, 0);
    (*data).pBody = NULL;//we dont know it yet
    (*data).restitution = 0.2f;
    (*data).rotation = 0.0f;
    (*data).texTileSize = sf::Vector2f(64, 64);
    (*data).color = sf::Color::White;

    rProjData = &get<projData>(m_projList[type]);
    (*rProjData).projType = type;
    (*rProjData).damage = T_Damage(500, 0);

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
    /**Check if lifetimes of projectiles should expire**/

    /**loop over the ProjListPairing, while looping over each ProjSPList inside of each element of ProjListPairing**/
    float timeElapsed = m_timer.getTimeElapsed();

    ProjSPList* pVec;
    auto it_pairEnd = m_projList.end();
    for(auto it_pair = m_projList.begin(); it_pair != it_pairEnd; ++it_pair)
    {
        pVec = &get<spList>(*it_pair);
        for(auto it = pVec->begin(); it != pVec->end(); ++it)
            if((*it)->changeLifeTimeRemain(-timeElapsed) <= 0)
                (*it)->endLife();
    }


    /**for each element in here
    ,make sure it isn't already asleep
    if it isn't put it to sleep
    and re insert it to the front,
    moving the free thing backwards
    and finally, clear the recoverList for future use**/

    /**take this new pointer, find it's position, find the position of the highest (used element) (free index-1)**/
    /**set this one to sleep, swap their positions, update positions, reduce index by 1**/
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
