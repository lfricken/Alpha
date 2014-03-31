#include "ControlManager.h"
#include "globals.h"

using namespace std;

ControlManager::ControlManager() : m_rUniverse(game.getGameUniverse()), m_rWindow(game.getGameWindow()), m_rGui(game.getGameOverlayManager().getGui())
{

}
ControlManager::~ControlManager()
{
    ///target->noController();
}
void ControlManager::add(const PlayerData& data)
{
    m_localPlayerList.push_back(tr1::shared_ptr<Player>(new Player(data)));
    /**camera setup**/
    m_localPlayerList.back()->getCamera().getView().setSize(static_cast<sf::Vector2f>(m_rWindow.getSize()));
    m_localPlayerList.back()->getCamera().getView().setCenter(sf::Vector2f(0, 0));
}
void ControlManager::setupControl()
{
    Chunk* chunk;
    for(vector<tr1::shared_ptr<Player> >::iterator it = m_localPlayerList.begin(); it != m_localPlayerList.end(); ++it)
    {
        chunk = m_rUniverse.getPhysTarget((*it)->getTargetName());
        if(chunk != NULL)
        {
            (*it)->linkControl(chunk);
        }
    }

    ///LOOP OVER SI HERE
}
Player* ControlManager::getPlayer(const std::string& target)
{
    for(vector<tr1::shared_ptr<Player> >::iterator it = m_localPlayerList.begin(); it != m_localPlayerList.end(); ++it)
    {
        if((*it)->getName() == target)
            return &(**it);
    }
    cout << "\nThere was an error finding player \"" << target << "\".";
    return NULL;
}
int ControlManager::pressedUpdate()
{
    float mass, fX, fY;///TEMP
    float force = 50;///TEMP
    float torque = 20;///TEMP

    for(vector<tr1::shared_ptr<Player> >::iterator it = m_localPlayerList.begin(); it != m_localPlayerList.end(); ++it)
    {
        m_pCPT = &**it;
        if(m_pCPT->hasTarget() && m_pCPT->isSending())
        {

            InputConfig& rInputConfig = m_pCPT->getInputConfig();///temp
            mass = m_pCPT->getTarget()->getBody()->GetMass();///temp
            m_bodyTarget = m_pCPT->getTarget()->getBody();///temp
            m_chunkTarget = m_pCPT->getTarget();

            if (sf::Mouse::isButtonPressed(rInputConfig.primary))
            {
                m_pCPT->setAim(m_rWindow.mapPixelToCoords(m_pCPT->getMouseCoords(), m_pCPT->getCamera().getView() ));
                m_pCPT->getTarget()->primary((*it)->getAim());
            }
            if (sf::Mouse::isButtonPressed(rInputConfig.secondary))
            {
                m_pCPT->setAim(m_rWindow.mapPixelToCoords((*it)->getMouseCoords(), m_pCPT->getCamera().getView() ));
                m_pCPT->getTarget()->secondary((*it)->getAim());
            }
            if (sf::Keyboard::isKeyPressed(rInputConfig.up))
            {
                m_chunkTarget->up();
            }
            if (sf::Keyboard::isKeyPressed(rInputConfig.down))
            {
                m_chunkTarget->down();

                ///temp
                fX = force*mass*sin(m_bodyTarget->GetAngle());
                fY = force*mass*cos(m_bodyTarget->GetAngle());
                m_bodyTarget->ApplyForceToCenter(b2Vec2(-fX, fY), true);
            }
            if (sf::Keyboard::isKeyPressed(rInputConfig.left))
            {
                m_chunkTarget->left();
                ///temp
                fX = force*mass*cos(m_bodyTarget->GetAngle());
                fY = force*mass*sin(m_bodyTarget->GetAngle());
                m_bodyTarget->ApplyForceToCenter(b2Vec2(-fX, -fY), true);
            }
            if (sf::Keyboard::isKeyPressed(rInputConfig.right))
            {
                m_chunkTarget->right();
                ///temp
                fX = force*mass*cos(m_bodyTarget->GetAngle());
                fY = force*mass*sin(m_bodyTarget->GetAngle());
                m_bodyTarget->ApplyForceToCenter(b2Vec2(fX, fY), true);
            }
            if (sf::Keyboard::isKeyPressed(rInputConfig.rollLeft))
            {
                m_chunkTarget->rollLeft();
                ///temp
                m_bodyTarget->ApplyTorque(-torque*mass, true);
            }
            if (sf::Keyboard::isKeyPressed(rInputConfig.rollRight))
            {
                m_chunkTarget->rollRight();
                ///temp
                m_bodyTarget->ApplyTorque(torque*mass, true);
            }
        }
    }
    ///LOOP OVER AI HERE
    return 0;
}
int ControlManager::choiceUpdate(sf::Event& rEvent)
{


    for(vector<tr1::shared_ptr<Player> >::iterator it = m_localPlayerList.begin(); it != m_localPlayerList.end(); ++it)
    {
        /**START OF PLAYER LOOP**/
        m_pCPT = &**it;

        /**THINGS WE SHOULD ALWAYS BE LISTENING FOR**/
        if (rEvent.type == sf::Event::Closed)//closed window
        {
            m_rWindow.close();
            return 1;///USE STATES
        }
        if (rEvent.type == sf::Event::KeyPressed)//on key press
        {
            if (rEvent.key.code == sf::Keyboard::Tab)
            {
                m_pCPT->toggleSending();
            }
            if (rEvent.key.code == sf::Keyboard::Escape)
            {
                cout << "\n\n\nExiting...";
                return 1;///USE STATES
            }
        }


        /**THINGS THAT DEPEND WHAT MODE WE ARE IN**/
        if(!m_pCPT->isSending())
            m_rGui.handleEvent(rEvent);/**GUI EVENT HANDLER**/
        else
        {
            if (rEvent.type == sf::Event::KeyPressed)//on key press
            {

            }
            if (rEvent.type == sf::Event::MouseMoved)//aim on mouse move
            {
                m_pCPT->setMouseCoords(sf::Vector2i(rEvent.mouseMove.x, rEvent.mouseMove.y));
                m_pCPT->setAim(m_rWindow.mapPixelToCoords(sf::Vector2i(rEvent.mouseMove.x, rEvent.mouseMove.y), m_pCPT->getCamera().getView()));
                if(m_pCPT->hasTarget())
                    m_pCPT->getTarget()->aim(m_pCPT->getAim());
            }
            if (rEvent.type == sf::Event::MouseWheelMoved)//zoom
            {
                float zoomChange = rEvent.mouseWheel.delta;
                if (zoomChange > 0)
                    zoomChange = 0.5;
                else if (zoomChange < 0)
                    zoomChange = 2.0;

                if(m_pCPT->hasTarget())
                {
                    if(zoomChange*m_pCPT->getCamera().getZoomLevel() > m_pCPT->getTarget()->getMaxZoom())
                        zoomChange = 1;
                    else if(zoomChange*m_pCPT->getCamera().getZoomLevel() < m_pCPT->getTarget()->getMinZoom())
                        zoomChange = 1;
                }

                m_pCPT->getCamera().getView().zoom(zoomChange);
                m_pCPT->getCamera().zoomFactor(zoomChange);

                sf::Vector2f smooth = m_pCPT->getCamera().getView().getCenter();//we do this so zooming to a spot is smoother
                m_pCPT->getCamera().getView().setCenter(sf::Vector2f( (m_pCPT->getAim().x+smooth.x)/2, (m_pCPT->getAim().y+smooth.y)/2 ));
            }


            if(m_pCPT->getPlayerMode() == "god")//cheats
                f_cheats(it, rEvent);



        }/**END OF PLAYER LOOP**/
    }
    ///LOOP OVER AI HERE??? what would we update?
    return 0;
}
void ControlManager::drawUpdate()
{
    for(vector<tr1::shared_ptr<Player> >::iterator it = m_localPlayerList.begin(); it != m_localPlayerList.end(); ++it)
    {
        if((*it)->getCamera().isTracking() && (*it)->hasTarget())
        {
            m_bodyTarget = (*it)->getTarget()->getBody();

            (*it)->getCamera().getView().setCenter(sf::Vector2f(scale*m_bodyTarget->GetPosition().x, scale*m_bodyTarget->GetPosition().y));
            (*it)->getCamera().getView().setRotation(180.0*m_bodyTarget->GetAngle()/PI);
        }
        m_rWindow.setView((*it)->getCamera().getView());
        m_rUniverse.draw();
    }
}
void ControlManager::f_cheats(vector<tr1::shared_ptr<Player> >::iterator it, sf::Event& rEvent)
{
    if (rEvent.type == sf::Event::KeyPressed)
    {
        if (rEvent.key.code == sf::Keyboard::T)
        {
            (*it)->getCamera().toggleTracking();
        }
        if (rEvent.key.code == sf::Keyboard::M)
        {
            cout << "\nMouse: (" << (*it)->getAim().x << "," << (*it)->getAim().y << ")";
            cout << "\nZoom: " << (*it)->getCamera().getZoomLevel();
        }
        if (rEvent.key.code == sf::Keyboard::P)
        {
            m_rUniverse.togglePause();
        }
        if (rEvent.key.code == sf::Keyboard::O)
        {
            m_rUniverse.toggleDebugDraw();
        }
        if (rEvent.key.code == sf::Keyboard::Delete)
        {
            m_rUniverse.removeBack();
        }
        if (rEvent.key.code == sf::Keyboard::Numpad8)
        {
            string target = "ship_2";
            cout << "\nControlling \"" << target << "\"";
            (*it)->linkControl(m_rUniverse.getPhysTarget(target));
        }
    }
}
