#include "Universe.h"

using namespace std;

Universe::Universe() : m_physWorld(b2Vec2(0,0))
{
    m_normalDraw = true;
    m_notPaused = true;

    m_timeStep = 1.0f / 60.0f;///this needs to be linked to frame rate
    m_velocityIterations = 4;
    m_positionIterations = 2;

    m_physWorld.SetContactListener(&m_contactListener);
}

Universe::~Universe()///unfinished
{

}
void Universe::removeBack()
{
    m_physList.pop_back();
}
void Universe::draw()///unfinished
{
    if(m_normalDraw)
    {
        for(vector<tr1::shared_ptr<Chunk> >::iterator it = m_physList.begin(); it != m_physList.end(); ++it)
        {
            (*it)->draw();
        }
    }
    else
        m_physWorld.DrawDebugData();
}
IOBase* Universe::getTarget(string target)///unfinished
{
    /**Loop through everything and find the target**/
    /*
    for(vector<IOBase*>::iterator it = m_namedObjects.begin(); it != m_namedObjects.end(); ++it)
    {
        if((*it)->getTargetName() == target)
            return (*it);
    }
    */
    return NULL;

}
Chunk* Universe::getPhysTarget(std::string target)
{
    for(vector<std::tr1::shared_ptr<Chunk> >::iterator it = m_physList.begin(); it != m_physList.end(); ++it)
    {
        if((*it)->getTargetName() == target)
            return &(**it);
    }
    return &(*m_physList.back());
}
b2World& Universe::getWorld()
{
    return m_physWorld;
}
void Universe::add(Chunk* pChunk)///unfinished
{
    m_physList.push_back(tr1::shared_ptr<Chunk>(pChunk));
}
void Universe::add(tr1::shared_ptr<Chunk> spChunk)
{
    m_physList.push_back(spChunk);
}
void Universe::toggleDebugDraw()
{
    m_normalDraw = !m_normalDraw;
}
void Universe::togglePause()
{
    m_notPaused = !m_notPaused;
}
void Universe::physStep()
{
    if(m_notPaused)
        m_physWorld.Step(m_timeStep, m_velocityIterations, m_positionIterations);///this needs to be linked to frame rate
}
