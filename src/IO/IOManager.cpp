#include "IOManager.h"
#include "Game.h"

using namespace std;

IOManager::IOManager(Game& game)
{
    m_pUniverse = &game.getGameUniverse();
    m_pOverlayManager = &game.getGameOverlayManager();
}
IOManager::~IOManager()//unfinished
{
    //dtor
}
void IOManager::recieve(Package& rPackage)//finished
{
    m_packageletList.push_back(Packagelet(rPackage.getDelay(), rPackage.getTargetID(), rPackage.getComFunc(), rPackage.getDestination(), rPackage.getParameter()));
}
void IOManager::update(const float timeChange)//unfinished, cause it got f'd up by adding the address to the package USE THIS CODE FOR GAME::setAddresses!!!!@@@@
{
    for(std::vector<Packagelet>::iterator it = m_packageletList.begin(); it != m_packageletList.end(); ++it)
    {
        (it)->timeRemaining -= timeChange;
        if((it)->timeRemaining <= 0)
        {
            if((it)->destination == Destination::UNIVERSE)
                m_currentTarget = m_pUniverse->getTarget((it)->targetID);
            else if((it)->destination == Destination::OVERLAYMANAGER)
                m_currentTarget = m_pOverlayManager->getTarget((it)->targetID);



            ///ect...

            if(m_currentTarget != NULL)
                (*m_currentTarget.*(it)->commandFunction)((it)->parameter);
           /// else//if you uncomment this things break
                ///ERROR LOG, couldnt find a target

            m_packageletList.erase(it);//pointer
            --it;
        }
    }
}
