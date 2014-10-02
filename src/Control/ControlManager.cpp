#include "ControlManager.hpp"
#include "globals.hpp"
#include "Sort.hpp"
#include "Convert.hpp"

using namespace std;

ControlManager::ControlManager()
{

}
ControlManager::~ControlManager()
{
    ///target->noController();?????????
}
void ControlManager::setupControl()
{
    Chunk* chunk;
    for(vector<tr1::shared_ptr<Player> >::iterator it = m_localPlayerList.begin(); it != m_localPlayerList.end(); ++it)
    {
        if((*it)->getTargetName() != "")//if we wanted to link to something
        {
            chunk = game.getGameUniverse().getPhysTarget((*it)->getTargetName());
            if(chunk != NULL)
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
std::vector<std::tr1::shared_ptr<Player> >& ControlManager::getPlayerList()
{
    return m_localPlayerList;
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
        Player* pPlayer = &**it;
        if((pPlayer->getState() == PlayerState::Playing))//if the player is in the playing state
        {
            if(pPlayer->getLinker().isLinked())//if we have a target
            {
                Chunk* pChunkTarget = pPlayer->getLinker().getTargetPtr();
                if(pChunkTarget->isControlEnabled())
                {
                    InputConfig& rInputConfig = pPlayer->getInputConfig();

                    if (sf::Mouse::isButtonPressed(rInputConfig.primary))
                    {
                        b2Vec2 worldAim = leon::sfTob2(game.getGameWindow().mapPixelToCoords(pPlayer->getMouseCoords(), pPlayer->getCamera().getView()));
                        pPlayer->setAim(worldAim);
                        pChunkTarget->primary(worldAim);
                    }
                    if (sf::Mouse::isButtonPressed(rInputConfig.secondary))
                    {
                        b2Vec2 worldAim = leon::sfTob2(game.getGameWindow().mapPixelToCoords(pPlayer->getMouseCoords(), pPlayer->getCamera().getView()));
                        pPlayer->setAim(worldAim);
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
    sf::RenderWindow* pWindow = &game.getGameWindow();
    static tgui::Widget::Ptr pDraggingWidget = nullptr;
    static sf::Vector2f draggingPosition;

    while(pWindow->pollEvent(rEvent))
    {



        for(vector<tr1::shared_ptr<Player> >::iterator it = m_localPlayerList.begin(); it != m_localPlayerList.end(); ++it)
        {
            /**START OF PLAYER LOOP**/
            Player* pPlayer = &**it;
            InputConfig& rInputConfig = pPlayer->getInputConfig();
            /**==============PRIORITY CHECKS======================THINGS WE SHOULD ALWAYS BE LISTENING FOR**/
            if (rEvent.type == sf::Event::Closed)//closed window
            {
                sf::Packet holder;
                game.input(holder, "exit");
            }
            if (rEvent.type == sf::Event::KeyPressed)//on key press
            {
                if (rEvent.key.code == sf::Keyboard::F1)
                {
                    pPlayer->setState(PlayerState::Editing);
                }
                if (rEvent.key.code == sf::Keyboard::F3)
                {
                    game.reloadWindow();
                }
                if (rEvent.key.code == sf::Keyboard::Tilde)
                {
                    cout << "\nTilde: " << FILELINE;
                    if(pPlayer->getState() == PlayerState::Editing)
                        pPlayer->setState(PlayerState::Playing);
                    else if(pPlayer->getState() == PlayerState::Playing)
                        pPlayer->setState(PlayerState::Interfacing);
                    else
                        pPlayer->setState(PlayerState::Playing);
                }
                if (rEvent.key.code == sf::Keyboard::Escape)
                {
                    cout << "\nEscape: " << FILELINE;
                }
                if(pPlayer->getLinker().isLinked())//if we have a target
                {
                    Chunk* pChunkTarget = pPlayer->getLinker().getTargetPtr();
                    if(pChunkTarget->isControlEnabled())//if that target accepts control
                    {
                        if (rEvent.key.code == rInputConfig.special_1)
                        {
                            cout << "\nSpecial Pressed.";
                            pChunkTarget->special_1();
                        }
                    }
                }
            }


            /**=================PLAY GAME====================this is for if we are trying to interact with the WORLD, like shooting or moving**/
            if(pPlayer->getState() == PlayerState::Playing)//we are playing the game
            {
                if (rEvent.type == sf::Event::KeyPressed)//on key press
                {

                }
                if (rEvent.type == sf::Event::MouseMoved)//aim on mouse move
                {
                    pPlayer->setMouseCoords(sf::Vector2i(rEvent.mouseMove.x, rEvent.mouseMove.y));

                    b2Vec2 worldAim = leon::sfTob2(game.getGameWindow().mapPixelToCoords(pPlayer->getMouseCoords(), pPlayer->getCamera().getView()));
                    pPlayer->setAim(worldAim);
                    if(pPlayer->getLinker().isLinked())
                        pPlayer->getLinker().getTargetPtr()->aim(worldAim);
                }
                if (rEvent.type == sf::Event::MouseWheelMoved)//control zooming of camera for a player
                {
                    int desiredZoom = -rEvent.mouseWheel.delta;//negative because it's backwards

                    if(desiredZoom > 0)//if we don't clamp the value, wierd stuff can happen
                        desiredZoom = 1;
                    else
                        desiredZoom = -1;

                    if(pPlayer->getLinker().isLinked())
                    {
                        int maxZoom = pPlayer->getLinker().getTargetPtr()->getZoomPool().getMaxValue();
                        int minZoom = pPlayer->getLinker().getTargetPtr()->getZoomPool().getMinValue();
                        int currentZoom = pPlayer->getCamera().getZoomLevel();

                        if(desiredZoom+currentZoom > maxZoom)
                            desiredZoom = 0;
                        else if(desiredZoom+currentZoom < minZoom)
                            desiredZoom = 0;
                    }

                    pPlayer->getCamera().zoom(desiredZoom);

                    b2Vec2 oldPos = pPlayer->getCamera().getCenter();/**we do this so zooming to a spot is smoother**/
                    b2Vec2 aimPos = pPlayer->getAim();
                    b2Vec2 smoothPos((oldPos.x+aimPos.x)/2, (oldPos.y+aimPos.y)/2);

                    pPlayer->getCamera().setCenter(smoothPos);
                }
                if(pPlayer->getPlayerMode() == PlayerMode::God)//cheats
                    f_cheats(it, rEvent);
            }


            /**============EDIT MODE===============  DRAGGING AROUND SCREEN ELEMENTS**/
            else if(pPlayer->getState() == PlayerState::Editing)//we are changing the positions of elements on screen
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
                                pDraggingWidget = widget;
                                draggingPosition = sf::Vector2f(rEvent.mouseButton.x, rEvent.mouseButton.y);
                            }
                        }
                    }
                }
                else if (rEvent.type == sf::Event::MouseButtonReleased)
                {
                    pDraggingWidget = nullptr;
                }
                else if (rEvent.type == sf::Event::MouseMoved)
                {
                    if (pDraggingWidget != nullptr)
                    {
                        pDraggingWidget->setPosition(pDraggingWidget->getPosition().x + rEvent.mouseMove.x - draggingPosition.x,
                                                     pDraggingWidget->getPosition().y + rEvent.mouseMove.y - draggingPosition.y);
                        draggingPosition = sf::Vector2f(rEvent.mouseMove.x, rEvent.mouseMove.y);
                    }
                }
            }

            /**========GUI============= HERE WE CAN CLICK ON BUTTONS AND INTERFACE WITH SCREEN ELEMENTS**/
            else if(pPlayer->getState() == PlayerState::Interfacing)//we are clicking buttons
                game.getGameOverlayManager().getGui().handleEvent(rEvent);

        }
        /**END OF PLAYER LOOP**/
    }


    ///LOOP OVER AI HERE??? what would we update exactly?
    return 0;
}
void ControlManager::drawUpdate()
{
    b2Body* pBody;
    b2Vec2 cameraVelocity(0,0);
    for(auto it = m_localPlayerList.begin(); it != m_localPlayerList.end(); ++it)
    {
        if((*it)->getCamera().isTracking() && (*it)->getLinker().isLinked())
        {
            pBody = (*it)->getLinker().getTargetPtr()->getBody();
            (*it)->getCamera().setCenter(pBody->GetPosition());
            cameraVelocity = pBody->GetLinearVelocity();

            if((*it)->getCamera().rotates())
                (*it)->getCamera().setRotation(pBody->GetAngle());//should the camera rotate with the target?
        }

        ///SOUND NOT DONE YET, WAITING FOR REPLY ON SPATIALIZATION POST
        sf::Listener::setPosition((*it)->getCamera().getView().getCenter().x, (*it)->getCamera().getView().getCenter().y, 0);
        sf::Listener::setDirection(sin((*it)->getCamera().getView().getRotation()), 0.0f, -cos((*it)->getCamera().getView().getRotation()));


        game.getRenderTarget().setView((*it)->getCamera().getView());
        //game.rendText_2.setView((*it)->getCamera().getView());
        game.getGameUniverse().draw(cameraVelocity);
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
            cout << "\n" << rUniverse.getBackwardPhys()->isAwake();
        }
    }
}
tgui::Widget::Ptr ControlManager::f_MouseOnWhichWidget(float x, float y, std::vector<tgui::Widget::Ptr>& widgets)
{
    for(std::vector<tgui::Widget::Ptr>::reverse_iterator it = widgets.rbegin(); it != widgets.rend(); ++it)
        if(((*it)->isVisible()) && ((*it)->isEnabled()) && ((*it)->mouseOnWidget(x, y)))
            return *it;

    return nullptr;
};
/**=================**/
/**=================**/
/**=====UPDATE=====**/
