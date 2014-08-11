#include "Universe.hpp"
#include "ClassType.hpp"
#include "Sort.hpp"
#include "globals.hpp"

using namespace std;

Universe::Universe() : IOBase(), m_physWorld(b2Vec2(0,0)), m_projAlloc(), m_gfxCompFactory()
{
    m_skippedTime = 0;
    m_normalDraw = true;
    m_paused = false;

    m_velocityIterations = 1;///how should these be set?
    m_positionIterations = 1;///how should these be set?
    m_timeStep = 1.0f/120.0f;///LOAD FROM FILE
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
IOBase* Universe::getTarget(const string& targetName)///unfinished
{
    IOBase* pTarget = NULL;

    pTarget = getPhysTarget(targetName);
    if(pTarget != NULL)
        return pTarget;

    ///pTarget = getGfxTarget(targetName);
    return pTarget;
}
IOBase* Universe::getTarget(unsigned int targetID)
{
    IOBase* pTarget = NULL;

    pTarget = getPhysTarget(targetID);
    if(pTarget != NULL)
        return pTarget;

    ///pTarget = getGfxTarget(targetID);
    return pTarget;
}
Chunk* Universe::getPhysTarget(const std::string& targetName)
{
    Chunk* pTarget = NULL;

    for(vector<std::tr1::shared_ptr<Chunk> >::iterator it = m_physList.begin(); it != m_physList.end(); ++it)
        if((*it)->getName() == targetName)
            pTarget = &(**it);

    return pTarget;
}
Chunk* Universe::getPhysTarget(unsigned int targetID)
{
    Chunk* pTarget = NULL;

    int location = BinarySearchPtrVector(m_physList, &Chunk::getID, targetID);
    if(location != -1)
        pTarget = &(*m_physList[location]);

    return pTarget;
}
Decoration* Universe::getGfxTarget(const std::string& targetName)
{

    Decoration* pTarget = NULL;

    for(vector<std::tr1::shared_ptr<Decoration> >::iterator it = m_gfxList.begin(); it != m_gfxList.end(); ++it)
///        if((*it)->getName() == targetName)
            pTarget = &(**it);

    return pTarget;
}
Decoration* Universe::getGfxTarget(unsigned int targetID)
{
    Decoration* pTarget = NULL;

   /// int location = BinarySearchPtrVector(m_gfxList, &Decoration::getID, targetID);
   /// if(location != -1)
   ///     pTarget = &(*m_gfxList[location]);

    return pTarget;
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
void Universe::add(Decoration* pDecor)
{
  ///  InsertPtrVector(m_gfxList, &IOBase::getID, tr1::shared_ptr<Decoration>(pDecor));
}
/**=================**/
/**=================**/
/**=====ADD=====**/


/**=====UPDATE=====**/
/**=================**/
/**=================**/
float Universe::physStep()
{
    if(not m_paused)
    {
        m_physWorld.Step(m_timeStep, m_velocityIterations, m_positionIterations);

        for(vector<tr1::shared_ptr<Chunk> >::iterator it = m_physList.begin(); it != m_physList.end(); ++it)
        {
            (*it)->physUpdate();
        }

        m_projAlloc.recoverProjectiles();
    }
    return m_timeStep;
}
void Universe::togglePause()
{
    m_paused = !m_paused;

    if(not m_paused)
        m_skippedTime += game.getTime()-m_pauseTime;
    else
        m_pauseTime = game.getTime();
}
float Universe::getTime() const
{
    if(m_paused)
        return m_pauseTime-m_skippedTime;
    else
        return game.getTime()-m_skippedTime;
}
void Universe::draw()
{
    if(m_normalDraw)
    {

        for(vector<tr1::shared_ptr<Chunk> >::iterator it = m_physList.begin(); it != m_physList.end(); ++it)
        {
            (*it)->draw();
        }

        m_gfxCompFactory.draw(game.getGameWindow());//things with a gfx component

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
GraphicsComponentFactory& Universe::getGfxCompFactory()
{
    return m_gfxCompFactory;
}
void Universe::removeBack()
{
    if(!m_physList.empty())
        m_physList.pop_back();
}
/**=====OTHER=====**/
/**=================**/
/**=================**/
