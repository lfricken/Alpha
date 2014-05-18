#include "ControlManager.h"
#include "globals.h"
#include "Sort.h"
#include "Angles.h"

using namespace std;

ControlManager::ControlManager() : m_rUniverse(game.getGameUniverse()), m_rWindow(game.getGameWindow()), m_rGui(game.getGameOverlayManager().getGui()), m_pDraggingWidget(nullptr)
{

}
ControlManager::~ControlManager()
{
    ///target->noController();
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


/**=====ADD=====**/
/**=================**/
/**=================**/
void ControlManager::add(std::tr1::shared_ptr<Player> spPlayer)
{
    InsertPtrVector(m_localPlayerList, &IOBase::getID, spPlayer);
}
/**=================**/
/**=================**/
/**=====ADD=====**/





/**=====GET_TARGETS=====**/
/**=================**/
/**=================**/
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
Player* ControlManager::getPlayer(const unsigned long long int targetID)
{
    int location = BinarySearchPtrVector(m_localPlayerList, &Player::getID, targetID);//<std::tr1::shared_ptr<Chunk>, Chunk, unsigned int>

    if(location == -1)
        return NULL;//couldnt find the target! :(
    else
        return &(*m_localPlayerList[location]);
}
/**=================**/
/**=================**/
/**=====GET_TARGETS=====**/





/**=====UPDATE=====**/
/**=================**/
/**=================**/
int ControlManager::pressedUpdate()
{
    float mass, fX, fY;///TEMP
    float force = 50;///TEMP
    float torque = 20;///TEMP

    for(vector<tr1::shared_ptr<Player> >::iterator it = m_localPlayerList.begin(); it != m_localPlayerList.end(); ++it)
    {
        m_pCPT = &**it;
        if((m_pCPT->getState() == PlayerState::Playing))//if the player is in the playing state
        {
            if(m_pCPT->hasTarget())//if we have a target
            {
                m_chunkTarget = m_pCPT->getTarget();
                if(m_chunkTarget->controlEnabled())
                {
                    InputConfig& rInputConfig = m_pCPT->getInputConfig();///temp
                    mass = m_chunkTarget->getBody()->GetMass();///temp
                    m_bodyTarget = m_chunkTarget->getBody();///temp


                    if (sf::Mouse::isButtonPressed(rInputConfig.primary))
                    {
                        m_pCPT->setAim(m_rWindow.mapPixelToCoords(m_pCPT->getMouseCoords(), m_pCPT->getCamera().getView() ));
                        m_chunkTarget->primary((*it)->getAim());
                    }
                    if (sf::Mouse::isButtonPressed(rInputConfig.secondary))
                    {
                        m_pCPT->setAim(m_rWindow.mapPixelToCoords((*it)->getMouseCoords(), m_pCPT->getCamera().getView() ));
                        m_chunkTarget->secondary((*it)->getAim());
                    }
                    if (sf::Keyboard::isKeyPressed(rInputConfig.up))
                    {
                        m_chunkTarget->up();/**should be how each of these if's looks**/
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
            if (rEvent.key.code == sf::Keyboard::F1)
            {
                m_pCPT->setState(PlayerState::Editing);
            }
            if (rEvent.key.code == sf::Keyboard::Tilde)
            {
                if(m_pCPT->getState() == PlayerState::Playing)
                    m_pCPT->setState(PlayerState::Interfacing);
                else
                    m_pCPT->setState(PlayerState::Playing);
            }
            if (rEvent.key.code == sf::Keyboard::Escape)
            {
                cout << "\n\n\nExiting...";
                return 1;///USE STATES
            }
        }


        /**THINGS THAT DEPEND WHAT MODE WE ARE IN**/
        if(m_pCPT->getState() == PlayerState::Playing)
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
            if (rEvent.type == sf::Event::MouseWheelMoved)//control zooming of camera for a player
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


            if(m_pCPT->getPlayerMode() == PlayerMode::God)//cheats
                f_cheats(it, rEvent);



        }/**END OF PLAYER LOOP**/
        else if(m_pCPT->getState() == PlayerState::Editing)
        {
            if (rEvent.type == sf::Event::MouseButtonPressed)
            {
                tgui::Widget::Ptr widget = f_MouseOnWhichWidget(rEvent.mouseButton.x, rEvent.mouseButton.y, m_rGui.getWidgets());
                if(widget != nullptr)
                {
                    if(widget->getWidgetType() == tgui::WidgetTypes::Type_Panel)
                    {
                        if(f_MouseOnWhichWidget(rEvent.mouseButton.x, rEvent.mouseButton.y, tgui::Panel::Ptr(widget)->getWidgets()) == nullptr)
                        {
                            m_pDraggingWidget = widget;
                            m_pDraggingPosition = sf::Vector2f(rEvent.mouseButton.x, rEvent.mouseButton.y);
                        }
                    }
                }
            }
            else if (rEvent.type == sf::Event::MouseButtonReleased)
            {
                m_pDraggingWidget = nullptr;
            }
            else if (rEvent.type == sf::Event::MouseMoved)
            {
                if (m_pDraggingWidget != nullptr)
                {
                    m_pDraggingWidget->setPosition(m_pDraggingWidget->getPosition().x + rEvent.mouseMove.x - m_pDraggingPosition.x,
                                                   m_pDraggingWidget->getPosition().y + rEvent.mouseMove.y - m_pDraggingPosition.y);

                    m_pDraggingPosition = sf::Vector2f(rEvent.mouseMove.x, rEvent.mouseMove.y);
                }
            }
        }
        else if(m_pCPT->getState() == PlayerState::Interfacing)
            m_rGui.handleEvent(rEvent);/**GUI EVENT HANDLER**/
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
            (*it)->getCamera().getView().setRotation(radToDeg(m_bodyTarget->GetAngle()));
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
tgui::Widget::Ptr ControlManager::f_MouseOnWhichWidget(float x, float y, std::vector<tgui::Widget::Ptr>& widgets)
{
    for (std::vector<tgui::Widget::Ptr>::reverse_iterator it = widgets.rbegin(); it != widgets.rend(); ++it)
        if (((*it)->isVisible()) && ((*it)->isEnabled()) && ((*it)->mouseOnWidget(x, y)))
            return *it;

    return nullptr;
};
/**=================**/
/**=================**/
/**=====UPDATE=====**/
