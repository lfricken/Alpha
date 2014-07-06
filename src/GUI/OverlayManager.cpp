#include "OverlayManager.h"
#include "Sort.h"

using namespace std;

OverlayManager::OverlayManager(sf::RenderWindow& window) : m_gui(window)
{
}
OverlayManager::~OverlayManager()
{

}



/**GENERIC**/
void OverlayManager::enableAll()
{
    for(auto it = m_panelList.begin(); it != m_panelList.end(); ++it)
        (*it)->getPanelPtr()->enable();
}
void OverlayManager::disableAll()
{
    for(auto it = m_panelList.begin(); it != m_panelList.end(); ++it)
        (*it)->getPanelPtr()->disable();
}
void OverlayManager::showAll()
{
    for(auto it = m_panelList.begin(); it != m_panelList.end(); ++it)
        (*it)->getPanelPtr()->show();
}
void OverlayManager::hideAll()
{
    for(auto it = m_panelList.begin(); it != m_panelList.end(); ++it)
        (*it)->getPanelPtr()->hide();
}
void OverlayManager::add(std::tr1::shared_ptr<leon::Panel> panel)
{
    InsertPtrVector(m_panelList, &IOBase::getID, panel);
}
leon::Panel* OverlayManager::getTarget(const std::string& target)
{
    for(auto it = m_panelList.cbegin(); it != m_panelList.cend(); ++it)
    {
        if((*it)->getName() == target)
        {
            leon::Panel* pIOBase = &(**it);//pointer
            return pIOBase;
        }
    }
    return NULL;
}
leon::Panel* OverlayManager::getTarget(unsigned int targetID)
{
    int location = BinarySearchPtrVector(m_panelList, &leon::Panel::getID, targetID);//<std::tr1::shared_ptr<Chunk>, Chunk, unsigned int>

    if(location == -1)
        return NULL;//couldnt find the target! :(
    else
        return &(*m_panelList[location]);
}
tgui::Gui& OverlayManager::getGui()
{
    return m_gui;
}
void OverlayManager::draw()
{
    m_gui.draw();
}




/**IO**/
IOBaseReturn OverlayManager::input(IOBaseArgs)
{
    IOBase::input(rInput, rCommand);
}
