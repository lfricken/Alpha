#include "Universe/Universe.h"

using namespace std;

Universe::Universe() : m_physWorld(b2Vec2(0,0))
{

}

Universe::~Universe()///unfinished
{
    //dtor
}

void Universe::draw()///unfinished
{

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
b2World& Universe::getWorld()
{
    return m_physWorld;
}
void Universe::add(Chunk* pChunk)///unfinished
{
    m_physList.push_back(tr1::shared_ptr<Chunk>(pChunk));
}
