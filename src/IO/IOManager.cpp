#include "Game.h"

using namespace std;

Universe& Game::getGameUniverse()
{
    return m_gameUniverse;
}
OverlayManager& Game::getGameOverlayManager()
{
    return m_gameOverlayManager;
}




IOManager::IOManager(Game& game) : m_rUniverse(game.getGameUniverse()), m_rOverlayManager(game.getGameOverlayManager())
{

}
IOManager::~IOManager()//unfinished
{
    //dtor
}
void IOManager::recieve(Package& rPackage)//finished
{
    m_packageList.push_back(tr1::shared_ptr<Package>(&rPackage));
}
void IOManager::update()//unfinished, cause it got f'd up by adding the address to the package USE THIS CODE FOR GAME::setAddresses!!!!@@@@
{
    m_elapsedTime = m_timer.restart();
    m_ftime = m_elapsedTime.asSeconds();

    for(vector<tr1::shared_ptr<Package> >::iterator it = m_packageList.begin(); it != m_packageList.end(); ++it)
    {
        (*it)->changeTime(-m_ftime);
        if((*it)->getTimeRemaining() <= 0)
        {
            (*it)->doActionOn(m_rUniverse.getTarget((*it)->getTargetID()));
            m_packageList.erase(it);//pointer
            --it;
        }
    }
}
