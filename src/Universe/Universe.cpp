#include "Universe.h"

using namespace std;


template<class S, class R,typename T>
int binary_find_ptr(vector<S>& container, T(R::*func)() const, T id)
{
    int first = 0;
    int last = container.size()-1;
    int middle = (first+last)/2;

    while(first <= last)
    {
        if (((*container[middle]).*func)() < id)
            first = middle + 1;
        else if (((*container[middle]).*func)() == id)
            return middle;
        else
            last = middle - 1;
        middle = (first + last)/2;
    }
    if (first > last)
        return -1;
    else
    {
        ///ERROR LOG
        return -1;
    }
}

Universe::Universe() : IOBase(IOBaseData("Universe", "Universe")), m_physWorld(b2Vec2(0,0))
{
    m_normalDraw = true;
    m_notPaused = true;

    m_velocityIterations = 3;///how should these be set?
    m_positionIterations = 3;///how should these be set?

    m_physWorld.SetContactListener(&m_contactListener);
}

Universe::~Universe()///unfinished
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
IOBase* Universe::getTarget(unsigned int targetID)///UNFINISHED
{
    int location = binary_find_ptr(m_physList, &Chunk::getID, targetID);//<std::tr1::shared_ptr<Chunk>, Chunk, unsigned int>
    ///also search non physlist stuff?

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
    return &(*m_physList.back());
}
Chunk* Universe::getPhysTarget(unsigned int target)///UNFINISHED
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
    pChunk->f_setID(++m_currentIDCount);
    m_physList.push_back(tr1::shared_ptr<Chunk>(pChunk));
}
void Universe::add(tr1::shared_ptr<Chunk> spChunk)
{
    spChunk->f_setID(++m_currentIDCount);
    m_physList.push_back(spChunk);
}
/**=================**/
/**=================**/
/**=====ADD=====**/






/**=====DRAWING=====**/
/**=================**/
/**=================**/
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
void Universe::toggleDebugDraw()
{
    m_normalDraw = !m_normalDraw;
}
/**=================**/
/**=================**/
/**=====DRAWING=====**/


/**=================**/
/**=================**/
/**=====OTHER=====**/
b2World& Universe::getWorld()
{
    return m_physWorld;
}
void Universe::togglePause()
{
    m_notPaused = !m_notPaused;
}
void Universe::physStep(const float timeChange)
{
    if(m_notPaused)
        m_physWorld.Step(timeChange, m_velocityIterations, m_positionIterations);
}
void Universe::removeBack()
{
    if(!m_physList.empty())
        m_physList.pop_back();
}
/**=====OTHER=====**/
/**=================**/
/**=================**/
