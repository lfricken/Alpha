#include "OverlayManager.h"
#include "BinaryVectorSearch.h"


using namespace std;

OverlayManager::OverlayManager(sf::RenderWindow& window) : m_gui(window)
{
}

OverlayManager::~OverlayManager()//unfinished
{
    //dtor
}


void OverlayManager::setActive(const std::string& target)//unfinished
{

}

void OverlayManager::deactivateAll()//unfinished
{

}
tgui::Gui& OverlayManager::getGui()
{
    return m_gui;
}
IOBase* OverlayManager::getTarget(const std::string& target)//finished
{
    for(vector<std::tr1::shared_ptr<leon::Panel> >::const_iterator it = m_panelList.begin(); it != m_panelList.end(); ++it)
    {
        if((*it)->getName() == target)
        {
            IOBase* pIOBase = &(**it);//pointer
            return pIOBase;
        }
    }
    return NULL;
}

IOBase* OverlayManager::getTarget(unsigned int targetID)///UNFINISHED
{
    int location = binary_find_ptr(m_panelList, &leon::Panel::getID, targetID);//<std::tr1::shared_ptr<Chunk>, Chunk, unsigned int>

    if(location == -1)
        return NULL;//couldnt find the target! :(
    else
        return &(*m_panelList[location]);
}
void OverlayManager::draw()
{
    m_gui.draw();
}
