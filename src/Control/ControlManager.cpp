#include "ControlManager.h"
#include "globals.h"
#include "Sort.h"
#include "Angles.h"

#include "GModule.h"///remove

using namespace std;

ControlManager::ControlManager() : m_pDraggingWidget(nullptr)
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
        chunk = game.getGameUniverse().getPhysTarget((*it)->getTargetName());
        if(chunk != NULL)
        {
            (*it)->getLinker().link(&chunk->getLinker());
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
Player* ControlManager::getPlayer(unsigned int targetID)
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
    for(vector<tr1::shared_ptr<Player> >::iterator it = m_localPlayerList.begin(); it != m_localPlayerList.end(); ++it)
    {
        m_pCPT = &**it;
        if((m_pCPT->getState() == PlayerState::Playing))//if the player is in the playing state
        {
            if(m_pCPT->getLinker().isLinked())//if we have a target
            {
                Chunk* pChunkTarget = m_pCPT->getLinker().getTargetPtr();
                if(pChunkTarget->isControlEnabled())
                {
                    InputConfig& rInputConfig = m_pCPT->getInputConfig();

                    if (sf::Mouse::isButtonPressed(rInputConfig.primary))
                    {
                        b2Vec2 worldAim = leon::sfTob2(game.getGameWindow().mapPixelToCoords(m_pCPT->getMouseCoords(), m_pCPT->getCamera().getView()));
                        m_pCPT->setAim(worldAim);
                        pChunkTarget->primary(worldAim);
                    }
                    if (sf::Mouse::isButtonPressed(rInputConfig.secondary))
                    {
                        b2Vec2 worldAim = leon::sfTob2(game.getGameWindow().mapPixelToCoords(m_pCPT->getMouseCoords(), m_pCPT->getCamera().getView()));
                        m_pCPT->setAim(worldAim);
                        pChunkTarget->secondary(worldAim);
                    }
                    if (sf::Keyboard::isKeyPressed(rInputConfig.up))
                    {
                        pChunkTarget->up();/**should be how each of these if's looks**/
                    }
                    if (sf::Keyboard::isKeyPressed(rInputConfig.down))
                    {
                        pChunkTarget->down();
                    }
                    if (sf::Keyboard::isKeyPressed(rInputConfig.left))
                    {
                        pChunkTarget->left();
                    }
                    if (sf::Keyboard::isKeyPressed(rInputConfig.right))
                    {
                        pChunkTarget->right();
                    }
                    if (sf::Keyboard::isKeyPressed(rInputConfig.rollLeft))
                    {
                        pChunkTarget->rollLeft();
                    }
                    if (sf::Keyboard::isKeyPressed(rInputConfig.rollRight))
                    {
                        pChunkTarget->rollRight();
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
            game.getGameWindow().close();
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
                return 1;///USE STATES, not numbers!
            }
        }


        /**THINGS THAT DEPEND WHAT MODE WE ARE IN**/
        if(m_pCPT->getState() == PlayerState::Playing)//we are playing the game
        {
            if (rEvent.type == sf::Event::KeyPressed)//on key press
            {

            }
            if (rEvent.type == sf::Event::MouseMoved)//aim on mouse move
            {
                m_pCPT->setMouseCoords(sf::Vector2i(rEvent.mouseMove.x, rEvent.mouseMove.y));

                b2Vec2 worldAim = leon::sfTob2(game.getGameWindow().mapPixelToCoords(m_pCPT->getMouseCoords(), m_pCPT->getCamera().getView()));
                m_pCPT->setAim(worldAim);
                if(m_pCPT->getLinker().isLinked())
                    m_pCPT->getLinker().getTargetPtr()->aim(worldAim);
            }
            if (rEvent.type == sf::Event::MouseWheelMoved)//control zooming of camera for a player
            {
                float zoomChange = rEvent.mouseWheel.delta;
                if (zoomChange > 0)
                    zoomChange = 0.5;
                else if (zoomChange < 0)
                    zoomChange = 2.0;

                if(m_pCPT->getLinker().isLinked())
                {
                    if(zoomChange*m_pCPT->getCamera().getZoomLevel() > m_pCPT->getLinker().getTargetPtr()->getMaxZoom())
                        zoomChange = 1;
                    else if(zoomChange*m_pCPT->getCamera().getZoomLevel() < m_pCPT->getLinker().getTargetPtr()->getMinZoom())
                        zoomChange = 1;
                }

                m_pCPT->getCamera().zoom(zoomChange);

                b2Vec2 oldPos = m_pCPT->getCamera().getCenter();/**we do this so zooming to a spot is smoother**/
                b2Vec2 aimPos = m_pCPT->getAim();
                b2Vec2 smoothPos((oldPos.x+aimPos.x)/2, (oldPos.y+aimPos.y)/2);

                m_pCPT->getCamera().setCenter(smoothPos);
            }


            if(m_pCPT->getPlayerMode() == PlayerMode::God)//cheats
                f_cheats(it, rEvent);



        }
        else if(m_pCPT->getState() == PlayerState::Editing)//we are changing the positions of elements on screen
        {
            if (rEvent.type == sf::Event::MouseButtonPressed)
            {
                tgui::Widget::Ptr widget = f_MouseOnWhichWidget(rEvent.mouseButton.x, rEvent.mouseButton.y, game.getGameOverlayManager().getGui().getWidgets());
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
        else if(m_pCPT->getState() == PlayerState::Interfacing)//we are clicking buttons
            game.getGameOverlayManager().getGui().handleEvent(rEvent);/**GUI EVENT HANDLER**/
    }/**END OF PLAYER LOOP**/
    ///LOOP OVER AI HERE??? what would we update exactly?
    return 0;
}
void ControlManager::drawUpdate()
{
    sf::Vector2f center;
    float rotation;///degrees
    for(auto it = m_localPlayerList.begin(); it != m_localPlayerList.end(); ++it)
    {
        if((*it)->getCamera().isTracking() && (*it)->getLinker().isLinked())
        {
            m_bodyTarget = (*it)->getLinker().getTargetPtr()->getBody();


            (*it)->getCamera().setCenter(m_bodyTarget->GetPosition());
            rotation = leon::radToDeg(m_bodyTarget->GetAngle());


            ///(*it)->getCamera().getView().setRotation(rotation);
        }

        ///SOUND NOT DONE YET, WAITING FOR REPLY ON SPATIALIZATION POST
        ///ALSO, THIS CODE CAUSES CRASH WHEN EXITING
        sf::Listener::setPosition((*it)->getCamera().getView().getCenter().x, (*it)->getCamera().getView().getCenter().y, 0);
        sf::Listener::setDirection(sin((*it)->getCamera().getView().getRotation()), 0.0f, -cos((*it)->getCamera().getView().getRotation()));

        game.getGameWindow().setView((*it)->getCamera().getView());
        game.getGameUniverse().draw();
    }
}
void ControlManager::f_cheats(vector<tr1::shared_ptr<Player> >::iterator it, sf::Event& rEvent)
{
    Universe& rUniverse = game.getGameUniverse();
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
            rUniverse.togglePause();
        }
        if (rEvent.key.code == sf::Keyboard::O)
        {
            rUniverse.toggleDebugDraw();
        }
        if (rEvent.key.code == sf::Keyboard::Delete)
        {
            rUniverse.removeBack();
        }
        if (rEvent.key.code == sf::Keyboard::K)
        {
            rUniverse.getBackwardPhys()->sleep();
        }
        if (rEvent.key.code == sf::Keyboard::J)
        {
            rUniverse.getBackwardPhys()->wake();
        }
        if (rEvent.key.code == sf::Keyboard::L)
        {
            cout << "\n" << rUniverse.getBackwardPhys()->getBody()->IsAwake();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
        {
            GModule* ptr = (*it)->getLinker().getTargetPtr()->getGModule("fixturePositionExample");
            if(ptr != NULL)
            {
                std::cout << "\n(" << ptr->getCenter().x << "," << ptr->getCenter().y << ")";
            }
            else
                cout << "\nError.";
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
