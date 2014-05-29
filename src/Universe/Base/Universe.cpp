#include "Universe.h"
#include "ClassType.h"
#include "Sort.h"

using namespace std;

Universe::Universe() : IOBase(), m_physWorld(b2Vec2(0,0)), m_projAlloc(&m_bedFinder)
{

    m_normalDraw = true;
    m_notPaused = true;

    m_velocityIterations = 1;///how should these be set?
    m_positionIterations = 1;///how should these be set?
    m_timeStep = 1.0f/60.0f;///LOAD FROM FILE
    m_maxIterations = 6;

    m_physWorld.SetContactListener(&m_contactListener);

    m_physWorld.SetDebugDraw(&m_debugDraw);
    m_debugDraw.SetFlags(b2Draw::e_shapeBit);///what does this do?
}

Universe::~Universe()
{

}

/**=====GET_TARGETS=====**/
/**=================**/
/**=================**/
IOBase* Universe::getTarget(const string& target)///unfinished
{
    /**Loop through everything and find the target**/
    for(vector<std::tr1::shared_ptr<Chunk> >::iterator it = m_physList.begin(); it != m_physList.end(); ++it)
    {
        if((*it)->getName() == target)
            return &(**it);
    }
    return NULL;
}
IOBase* Universe::getTarget(unsigned long long int targetID)
{
    ///first search non physlist stuff
    int location = BinarySearchPtrVector(m_physList, &Chunk::getID, targetID);//<std::tr1::shared_ptr<Chunk>, Chunk, unsigned int>

    if(location == -1)
        return NULL;//couldnt find the target! :(
    else
        return &(*m_physList[location]);
}
Chunk* Universe::getPhysTarget(const std::string& target)
{
    for(vector<std::tr1::shared_ptr<Chunk> >::iterator it = m_physList.begin(); it != m_physList.end(); ++it)
    {
        if((*it)->getName() == target)
            return &(**it);
    }
    return NULL;
}
Chunk* Universe::getPhysTarget(unsigned long long int targetID)
{
    return NULL;
}
Chunk* Universe::getBackwardPhys()
{
    return &*m_physList.back();
}
/**=================**/
/**=================**/
/**=====GET_TARGETS=====**/


/**=====ADD=====**/
/**=================**/
/**=================**/
void Universe::add(Chunk* pChunk)
{
    InsertPtrVector(m_physList, &IOBase::getID, tr1::shared_ptr<Chunk>(pChunk));
}
void Universe::add(tr1::shared_ptr<Chunk> spChunk)
{
    InsertPtrVector(m_physList, &IOBase::getID, spChunk);
}
/**=================**/
/**=================**/
/**=====ADD=====**/


/**=====UPDATE=====**/
/**=================**/
/**=================**/
float Universe::physStep()
{
    if(m_notPaused)
    {
        for(vector<tr1::shared_ptr<Chunk> >::iterator it = m_physList.begin(); it != m_physList.end(); ++it)
        {
            (*it)->physUpdate();
        }
        m_physWorld.Step(m_timeStep, m_velocityIterations, m_positionIterations);
        m_projAlloc.recoverProjectiles();
    }
    return m_timeStep;
}
void Universe::togglePause()
{
    m_notPaused = !m_notPaused;
}
void Universe::draw()
{
    if(m_normalDraw)
    {
        for(vector<tr1::shared_ptr<Chunk> >::iterator it = m_physList.begin(); it != m_physList.end(); ++it)
        {
            (*it)->draw();
        }
        m_projAlloc.draw();
        ///also draw graphics objects?? maybe we should have another section for that??
    }
    else
        m_physWorld.DrawDebugData();
}
void Universe::toggleDebugDraw()
{
    m_normalDraw = !m_normalDraw;
}
/**=================**/
/**=================**/
/**=====UPDATE=====**/


/**=================**/
/**=================**/
/**=====OTHER=====**/
b2World& Universe::getWorld()
{
    return m_physWorld;
}
BedFinder& Universe::getBedFinder()
{
    return m_bedFinder;
}
ProjectileAllocator& Universe::getProjAlloc()
{
    return m_projAlloc;
}
void Universe::removeBack()
{
    if(!m_physList.empty())
        m_physList.pop_back();
}
/**=====OTHER=====**/
/**=================**/
/**=================**/
