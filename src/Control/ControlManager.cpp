#include "ControlManager.h"

#include <globals.h>

using namespace std;


ControlManager::ControlManager() : m_rUniverse(game.getGameUniverse()), m_rWindow(game.getGameWindow())
{
    ///We actually should load this from a file
    m_localPlayerList.push_back(Player());
    m_localPlayerList.front().playerName = "player_1";
    m_localPlayerList.front().playerMode = "god";

    m_localPlayerList.front().up = sf::Keyboard::W;
    m_localPlayerList.front().down = sf::Keyboard::S;
    m_localPlayerList.front().left = sf::Keyboard::Q;
    m_localPlayerList.front().right = sf::Keyboard::E;
    m_localPlayerList.front().rollLeft = sf::Keyboard::A;
    m_localPlayerList.front().rollRight = sf::Keyboard::D;
    m_localPlayerList.front().special_1 = sf::Keyboard::R;
    m_localPlayerList.front().special_2 = sf::Keyboard::F;
    m_localPlayerList.front().special_3 = sf::Keyboard::C;
    m_localPlayerList.front().special_4 = sf::Keyboard::X;

    m_localPlayerList.front().primary = sf::Mouse::Left;
    m_localPlayerList.front().secondary = sf::Mouse::Right;

    m_localPlayerList.front().camera.getView().setSize(sf::Vector2f(1200, 600));
    m_localPlayerList.front().camera.getView().setCenter(sf::Vector2f(0, 0));
}

ControlManager::~ControlManager()
{

}
Player& ControlManager::getPlayer(const std::string& target)
{
    for(vector<Player>::iterator it = m_localPlayerList.begin(); it != m_localPlayerList.end(); ++it)
    {
        if(it->playerName == target)
            return *it;
    }
    cout << "\nThere was an error finding player \"" << target << "\".";
    return m_localPlayerList.front();
}
int ControlManager::choiceUpdate()
{

    float mass, fX, fY;
    float force = 50;
    float torque = 20;
    float mult = 1;
    b2Body* body;
    for(vector<Player>::iterator it = m_localPlayerList.begin(); it != m_localPlayerList.end(); ++it)
    {
        mass = it->target->getBody()->GetMass();
        body = it->target->getBody();
        if (sf::Keyboard::isKeyPressed(it->up))
        {
            fX = force*mass*sin(body->GetAngle());
            fY = force*mass*cos(body->GetAngle());
            body->ApplyForceToCenter(b2Vec2(fX,-fY), true);
            ///it->target->up();
        }
        if (sf::Keyboard::isKeyPressed(it->down))
        {
            fX = force*mass*sin(body->GetAngle());
            fY = force*mass*cos(body->GetAngle());
            body->ApplyForceToCenter(b2Vec2(-fX, fY), true);
        }
        if (sf::Keyboard::isKeyPressed(it->left))
        {
            fX = force*mass*cos(body->GetAngle());
            fY = force*mass*sin(body->GetAngle());
            body->ApplyForceToCenter(b2Vec2(-fX, -fY), true);
        }
        if (sf::Keyboard::isKeyPressed(it->right))
        {
            fX = force*mass*cos(body->GetAngle());
            fY = force*mass*sin(body->GetAngle());
            body->ApplyForceToCenter(b2Vec2(fX, fY), true);
        }
        if (sf::Keyboard::isKeyPressed(it->rollLeft))
        {
            body->ApplyTorque(-torque*mass, true);
        }
        if (sf::Keyboard::isKeyPressed(it->rollRight))
        {
            body->ApplyTorque(torque*mass, true);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            cout << "\n\n\nExiting...";
            return 1;///USE STATES
        }







        while (m_rWindow.pollEvent(m_event))//zoom stuff
        {
            if (m_event.type == sf::Event::Closed)
            {
                m_rWindow.close();
                return 1;///USE STATES
            }
            if (m_event.type == sf::Event::KeyPressed)
            {

            }
            if (m_event.type == sf::Event::MouseMoved)
            {
                it->mouseCoord = m_rWindow.mapPixelToCoords(sf::Vector2i(m_event.mouseMove.x, m_event.mouseMove.y), it->camera.getView());
            }
            if (m_event.type == sf::Event::MouseWheelMoved)
            {
                float zoomChange = m_event.mouseWheel.delta;
                if (zoomChange > 0)
                    zoomChange = 0.5;
                else if (zoomChange < 0)
                    zoomChange = 2.0;

                it->camera.getView().zoom(zoomChange);
                it->camera.zoomFactor(zoomChange);

                sf::Vector2f smooth = it->camera.getView().getCenter();//we do this so zooming to a spot is smoother
                it->camera.getView().setCenter(sf::Vector2f( (it->mouseCoord.x+smooth.x)/2, (it->mouseCoord.y+smooth.y)/2 ));
            }

            if(it->playerMode == "god")
                f_cheats(it);
        }


        if(it->camera.isTracking())
        {
            it->camera.getView().setCenter(sf::Vector2f(scale*body->GetPosition().x, scale*body->GetPosition().y));
            it->camera.getView().setRotation(180.0*body->GetAngle()/PI);
        }
    }
    return 0;
}
void ControlManager::drawUpdate()
{
    for(vector<Player>::iterator it = m_localPlayerList.begin(); it != m_localPlayerList.end(); ++it)
    {
        m_rWindow.setView(it->camera.getView());
        m_rUniverse.draw();
    }
}
void ControlManager::f_cheats(vector<Player>::iterator it)
{


    if (m_event.type == sf::Event::KeyPressed)
    {
        if (m_event.key.code == sf::Keyboard::T)
        {
            it->camera.toggleTracking();
        }
        if (m_event.key.code == sf::Keyboard::M)
        {
            cout << "\nMouse: (" << it->mouseCoord.x << "," << it->mouseCoord.y << ")";
            cout << "\nZoom: " << it->camera.getZoomLevel();
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
    }

}
