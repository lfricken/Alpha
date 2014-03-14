#include "ControlManager.h"
#include "globals.h"

using namespace std;


ControlManager::ControlManager() : m_rUniverse(game.getGameUniverse()), m_rWindow(game.getGameWindow())
{
    ///We actually should load this from a file
    m_localPlayerList.push_back(Player(1));
    m_localPlayerList.front().setName("player_1");
    m_localPlayerList.front().setPlayerMode("god");

    InputConfig& rInputConfig = m_localPlayerList.front().getInputConfig();


    rInputConfig.up = sf::Keyboard::W;
    rInputConfig.down = sf::Keyboard::S;
    rInputConfig.left = sf::Keyboard::Q;
    rInputConfig.right = sf::Keyboard::E;
    rInputConfig.rollLeft = sf::Keyboard::A;
    rInputConfig.rollRight = sf::Keyboard::D;
    rInputConfig.special_1 = sf::Keyboard::R;
    rInputConfig.special_2 = sf::Keyboard::F;
    rInputConfig.special_3 = sf::Keyboard::C;
    rInputConfig.special_4 = sf::Keyboard::X;

    rInputConfig.primary = sf::Mouse::Left;
    rInputConfig.secondary = sf::Mouse::Right;

    m_localPlayerList.front().getCamera().getView().setSize(static_cast<sf::Vector2f>(m_rWindow.getSize()));
    m_localPlayerList.front().getCamera().getView().setCenter(sf::Vector2f(0, 0));

    ///m_localPlayerList.front().hasController(this);
}

ControlManager::~ControlManager()
{
    ///target->noController();
}
Player& ControlManager::getPlayer(const std::string& target)
{
    for(vector<Player>::iterator it = m_localPlayerList.begin(); it != m_localPlayerList.end(); ++it)
    {
        if(it->getName() == target)
            return *it;
    }
    cout << "\nThere was an error finding player \"" << target << "\".";
    return m_localPlayerList.front();
}
int ControlManager::choiceUpdate()
{
    float mass, fX, fY;///TEMP
    float force = 50;///TEMP
    float torque = 20;///TEMP

    b2Body* body;
    for(vector<Player>::iterator it = m_localPlayerList.begin(); it != m_localPlayerList.end(); ++it)
    {
        while (m_rWindow.pollEvent(m_event))//zoom stuff
        {
            if (m_event.type == sf::Event::Closed)
            {
                m_rWindow.close();
                return 1;///USE STATES
            }
            if (m_event.type == sf::Event::KeyPressed)
            {
                //toggle stuff
            }
            if (m_event.type == sf::Event::MouseMoved)
            {
                it->setAim(m_rWindow.mapPixelToCoords(sf::Vector2i(m_event.mouseMove.x, m_event.mouseMove.y), it->getCamera().getView()));
            }
            if (m_event.type == sf::Event::MouseWheelMoved)
            {
                float zoomChange = m_event.mouseWheel.delta;
                if (zoomChange > 0)
                    zoomChange = 0.5;
                else if (zoomChange < 0)
                    zoomChange = 2.0;

                it->getCamera().getView().zoom(zoomChange);
                it->getCamera().zoomFactor(zoomChange);

                sf::Vector2f smooth = it->getCamera().getView().getCenter();//we do this so zooming to a spot is smoother
                it->getCamera().getView().setCenter(sf::Vector2f( (it->getAim().x+smooth.x)/2, (it->getAim().y+smooth.y)/2 ));
            }

            if(it->getPlayerMode() == "god")
                f_cheats(it);
        }

        if(it->hasTarget())
        {

            InputConfig& rInputConfig = it->getInputConfig();
            mass = it->getTarget()->getBody()->GetMass();
            body = it->getTarget()->getBody();
            if (sf::Keyboard::isKeyPressed(rInputConfig.up))
            {
                it->getTarget()->up();
                ///it->target->up();
            }
            if (sf::Keyboard::isKeyPressed(rInputConfig.down))
            {
                it->getTarget()->down();
                fX = force*mass*sin(body->GetAngle());
                fY = force*mass*cos(body->GetAngle());
                body->ApplyForceToCenter(b2Vec2(-fX, fY), true);
            }
            if (sf::Keyboard::isKeyPressed(rInputConfig.left))
            {
                fX = force*mass*cos(body->GetAngle());
                fY = force*mass*sin(body->GetAngle());
                body->ApplyForceToCenter(b2Vec2(-fX, -fY), true);
            }
            if (sf::Keyboard::isKeyPressed(rInputConfig.right))
            {
                fX = force*mass*cos(body->GetAngle());
                fY = force*mass*sin(body->GetAngle());
                body->ApplyForceToCenter(b2Vec2(fX, fY), true);
            }
            if (sf::Keyboard::isKeyPressed(rInputConfig.rollLeft))
            {
                body->ApplyTorque(-torque*mass, true);
            }
            if (sf::Keyboard::isKeyPressed(rInputConfig.rollRight))
            {
                body->ApplyTorque(torque*mass, true);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                cout << "\n\n\nExiting...";
                return 1;///USE STATES
            }
            if(it->getCamera().isTracking())
            {
                it->getCamera().getView().setCenter(sf::Vector2f(scale*body->GetPosition().x, scale*body->GetPosition().y));
                it->getCamera().getView().setRotation(180.0*body->GetAngle()/PI);
            }
        }
    }/**END OF PLAYER LOOP**/


    ///LOOP OVER AI HERE
    return 0;
}
void ControlManager::drawUpdate()
{
    for(vector<Player>::iterator it = m_localPlayerList.begin(); it != m_localPlayerList.end(); ++it)
    {
        m_rWindow.setView(it->getCamera().getView());
        m_rUniverse.draw();
    }
}
void ControlManager::f_cheats(vector<Player>::iterator it)
{
    if (m_event.type == sf::Event::KeyPressed)
    {
        if (m_event.key.code == sf::Keyboard::T)
        {
            it->getCamera().toggleTracking();
        }
        if (m_event.key.code == sf::Keyboard::M)
        {
            cout << "\nMouse: (" << it->getAim().x << "," << it->getAim().y << ")";
            cout << "\nZoom: " << it->getCamera().getZoomLevel();
        }
        if (m_event.key.code == sf::Keyboard::P)
        {
            m_rUniverse.togglePause();
        }
        if (m_event.key.code == sf::Keyboard::O)
        {
            m_rUniverse.toggleDebugDraw();
        }
        if (m_event.key.code == sf::Keyboard::Delete)
        {
            m_rUniverse.removeBack();
        }
        if (m_event.key.code == sf::Keyboard::Numpad8)
        {
            string target = "ship_1";
            cout << "\nControlling \"" << target << "\"";
            it->linkControl(m_rUniverse.getPhysTarget(target));
        }
    }
}
