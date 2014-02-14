#include <Game/Game.h>

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
    m_packageList.push_back(rPackage);
}
void IOManager::update()//unfinished, cause it got f'd up by adding the address to the package USE THIS CODE FOR GAME::setAddresses!!!!@@@@
{
    m_elapsedTime = m_timer.restart();
    m_ftime = m_elapsedTime.asSeconds();

    for(vector<Package>::iterator it = m_packageList.begin(); it != m_packageList.end(); ++it)
    {
        it->delay -= m_ftime;
        if(it->delay <= 0)
        {
            m_pCurrentTarget = m_rUniverse.getTarget(it->targetName);
            if(m_pCurrentTarget == NULL)
            {
                m_pCurrentTarget = m_rOverlayManager.getTarget(it->targetName);
            }


            if(m_pCurrentTarget == NULL)
            {
            }
            else
            {
                m_pCurrentTarget->input(*it);
            }
            m_packageList.erase(it);//pointer
            --it;
        }
    }
}
