#include "Universe.h"
#include "Types.h"
#include "Sort.h"

using namespace std;

Universe::Universe() : IOBase(), m_physWorld(b2Vec2(0,0))
{
    m_normalDraw = true;
    m_notPaused = true;

    m_velocityIterations = 4;///how should these be set?
    m_positionIterations = 2;///how should these be set?
    m_timeStep = 1.0f/120.0f;
    m_maxIterations = 6;

    m_physWorld.SetContactListener(&m_contactListener);

    m_physWorld.SetDebugDraw(&m_debugDraw);
    m_debugDraw.SetFlags(b2Draw::e_shapeBit);
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
void Universe::removeBack()
{
    if(!m_physList.empty())
        m_physList.pop_back();
}
/**=====OTHER=====**/
/**=================**/
/**=================**/
