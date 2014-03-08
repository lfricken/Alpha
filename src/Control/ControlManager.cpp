#include "ControlManager.h"

#include <globals.h>

using namespace std;


ControlManager::ControlManager() : m_rUniverse(game.getGameUniverse()), m_rWindow(game.getGameWindow())
{
    ///We actually should load this from a file
    m_localPlayerList.push_back(Player());
    m_localPlayerList.front().playerName = "player_1";

    m_localPlayerList.front().up = sf::Keyboard::W;
    m_localPlayerList.front().down = sf::Keyboard::S;
    m_localPlayerList.front().left = sf::Keyboard::A;
    m_localPlayerList.front().right = sf::Keyboard::D;
    m_localPlayerList.front().rollLeft = sf::Keyboard::Q;
    m_localPlayerList.front().rollRight = sf::Keyboard::E;
    m_localPlayerList.front().special_1 = sf::Keyboard::R;
    m_localPlayerList.front().special_2 = sf::Keyboard::F;
    m_localPlayerList.front().special_3 = sf::Keyboard::C;
    m_localPlayerList.front().special_4 = sf::Keyboard::X;

    m_localPlayerList.front().primary = sf::Mouse::Left;
    m_localPlayerList.front().secondary = sf::Mouse::Right;

    m_localPlayerList.front().view.setSize(sf::Vector2f(1200, 600));
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
void ControlManager::choiceUpdate()
{

    float mass, fX, fY;
    float force = 500;
    float torque = 5;
    float mult = 1;
    b2Body* body;
    for(vector<Player>::iterator it = m_localPlayerList.begin(); it != m_localPlayerList.end(); ++it)
    {
        mass = it->target->getBody()->GetMass();
        body = it->target->getBody();
        if (sf::Keyboard::isKeyPressed(it->up))
        {
           /// body->ApplyForceToCenter()
            fX = force*mult*sin(body->GetAngle());
            fY = force*mult*cos(body->GetAngle());
            body->ApplyForce(b2Vec2(fX,-fY),body->GetWorldCenter(), true);
        }
        if (sf::Keyboard::isKeyPressed(it->down))
        {
            //down
        }
        if (sf::Keyboard::isKeyPressed(it->left))
        {
            //left
        }
        if (sf::Keyboard::isKeyPressed(it->right))
        {
            //right
        }
    }
}
void ControlManager::drawUpdate()
{
    for(vector<Player>::iterator it = m_localPlayerList.begin(); it != m_localPlayerList.end(); ++it)
    {
        m_rWindow.setView(it->view);
        m_rUniverse.draw();
    }
}
