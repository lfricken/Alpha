#ifndef PLAYER_H
#define PLAYER_H
#include <Intelligence.h>
#include <Camera.h>

class Player : public Intelligence
{
public:
    Player(int playerNumber);
    virtual ~Player();


protected:
private:
    Camera camera;
    std::string playerMode;///STATE INSTEAD??

    sf::Keyboard::Key m_up;
    sf::Keyboard::Key m_down;
    sf::Keyboard::Key m_left;
    sf::Keyboard::Key m_right;
    sf::Keyboard::Key m_rollLeft;
    sf::Keyboard::Key m_rollRight;
    sf::Keyboard::Key m_special_1;
    sf::Keyboard::Key m_special_2;
    sf::Keyboard::Key m_special_3;
    sf::Keyboard::Key m_special_4;

    sf::Mouse::Button m_primary;
    sf::Mouse::Button m_secondary;
};

#endif // PLAYER_H
