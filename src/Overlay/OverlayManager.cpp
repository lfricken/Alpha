#include "OverlayManager.h"

using namespace std;

OverlayManager::OverlayManager()
{
    //ctor
}

OverlayManager::~OverlayManager()//unfinished
{
    //dtor
}


void OverlayManager::setActive(string target)//unfinished
{

}

void OverlayManager::deactivateAll()//unfinished
{

}

IOBase* OverlayManager::getTarget(string target)//finished
{
    for(vector<Overlay>::iterator it = m_overlayList.begin(); it != m_overlayList.end(); ++it)
    {
        if(it->getName() == target)
        {
            IOBase* pIOBase = &(*it);//pointer
            return pIOBase;
        }
    }
    return NULL;
}
void OverlayManager::draw()
{

}
