#include "Universe/Universe.h"

using namespace std;

Universe::Universe() : m_physWorld(b2Vec2(0,0))
{

}

Universe::~Universe()//unfinished
{
    //dtor
}

void Universe::draw()//unfinished
{

}

IOBase* Universe::getTarget(string target)//finished
{
    for(vector<IOBase*>::iterator it = m_namedObjects.begin(); it != m_namedObjects.end(); ++it)
    {
        if((*it)->getTargetName() == target)
            return (*it);
    }

    return NULL;
}
b2World& Universe::getWorld()
{
    return m_physWorld;
}
void Universe::load(string filename)//unfinished
{

}
