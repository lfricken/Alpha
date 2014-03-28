#include "ControlManager.h"
#include "globals.h"

using namespace std;

ControlManager::ControlManager() : m_rUniverse(game.getGameUniverse()), m_rWindow(game.getGameWindow())
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
            (*it)->linkControl(chunk);
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

        if((*it)->hasTarget())
        {

            InputConfig& rInputConfig = (*it)->getInputConfig();///temp
            mass = (*it)->getTarget()->getBody()->GetMass();///temp
            m_bodyTarget = (*it)->getTarget()->getBody();///temp
            m_chunkTarget = (*it)->getTarget();

            if (sf::Mouse::isButtonPressed(rInputConfig.primary))
            {
                (*it)->setAim(m_rWindow.mapPixelToCoords((*it)->getMouseCoords(), (*it)->getCamera().getView() ));
                (*it)->getTarget()->primary((*it)->getAim());
            }
            if (sf::Mouse::isButtonPressed(rInputConfig.secondary))
            {
                (*it)->setAim(m_rWindow.mapPixelToCoords((*it)->getMouseCoords(), (*it)->getCamera().getView() ));
                (*it)->getTarget()->primary((*it)->getAim());
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

        if (rEvent.type == sf::Event::Closed)//closed window
        {
            m_rWindow.close();
            return 1;///USE STATES
        }
        if (rEvent.type == sf::Event::KeyPressed)//on key press
        {
            if (rEvent.key.code == sf::Keyboard::Escape)
            {
                cout << "\n\n\nExiting...";
                return 1;///USE STATES
            }
        }
        if (rEvent.type == sf::Event::MouseMoved)//aim on mouse move
        {
            (*it)->setMouseCoords(sf::Vector2i(rEvent.mouseMove.x, rEvent.mouseMove.y));
            (*it)->setAim(m_rWindow.mapPixelToCoords(sf::Vector2i(rEvent.mouseMove.x, rEvent.mouseMove.y), (*it)->getCamera().getView()));
            if((*it)->hasTarget())
                (*it)->getTarget()->aim((*it)->getAim());
        }
        if (rEvent.type == sf::Event::MouseWheelMoved)//zoom
        {
            float zoomChange = rEvent.mouseWheel.delta;
            if (zoomChange > 0)
                zoomChange = 0.5;
            else if (zoomChange < 0)
                zoomChange = 2.0;

            if((*it)->hasTarget())
            {
                if(zoomChange*(*it)->getCamera().getZoomLevel() > (*it)->getTarget()->getMaxZoom())
                    zoomChange = 1;
                else if(zoomChange*(*it)->getCamera().getZoomLevel() < (*it)->getTarget()->getMinZoom())
                    zoomChange = 1;
            }

            (*it)->getCamera().getView().zoom(zoomChange);
            (*it)->getCamera().zoomFactor(zoomChange);

            sf::Vector2f smooth = (*it)->getCamera().getView().getCenter();//we do this so zooming to a spot is smoother
            (*it)->getCamera().getView().setCenter(sf::Vector2f( ((*it)->getAim().x+smooth.x)/2, ((*it)->getAim().y+smooth.y)/2 ));
        }


        if((*it)->getPlayerMode() == "god")//cheats
            f_cheats(it, rEvent);


    }/**END OF PLAYER LOOP**/

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
