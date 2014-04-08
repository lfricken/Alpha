#include "OverlayManager.h"
#include "BinaryVectorSearch.h"
#include "Sort.h"

using namespace std;

OverlayManager::OverlayManager(sf::RenderWindow& window) : m_gui(window)
{
}
OverlayManager::~OverlayManager()
{
    //dtor
}
void OverlayManager::deactivateAll()
{

}



/**===========**/
/**====GET====**/
/**===========**/
tgui::Gui& OverlayManager::getGui()
{
    return m_gui;
}
leon::Panel* OverlayManager::getTarget(const std::string& target)
{
    for(vector<std::tr1::shared_ptr<leon::Panel> >::const_iterator it = m_panelList.begin(); it != m_panelList.end(); ++it)
    {
        if((*it)->getName() == target)
        {
            leon::Panel* pIOBase = &(**it);//pointer
            return pIOBase;
        }
    }
    return NULL;
}
leon::Panel* OverlayManager::getTarget(unsigned long long int targetID)
{
    int location = BinarySearchPtrVector(m_panelList, &leon::Panel::getID, targetID);//<std::tr1::shared_ptr<Chunk>, Chunk, unsigned int>

    if(location == -1)
        return NULL;//couldnt find the target! :(
    else
        return &(*m_panelList[location]);
}
/**===========**/
/**====GET====**/
/**===========**/




/**===========**/
/**====ADD====**/
/**===========**/
void OverlayManager::add(std::tr1::shared_ptr<leon::Panel> panel)
{
    InsertPtrVector(m_panelList, &IOBase::getID, panel);
}
/**===========**/
/**====ADD====**/
/**===========**/


void OverlayManager::draw()
{
    m_gui.draw();
}
