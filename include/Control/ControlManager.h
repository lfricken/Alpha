#ifndef CONTROLMANAGER_H
#define CONTROLMANAGER_H
#include <stdafx.h>
#include <Chunk.h>
#include <Universe.h>

struct Player
{
    std::string playerName;

    sf::Keyboard::Key up;
    sf::Keyboard::Key down;
    sf::Keyboard::Key left;
    sf::Keyboard::Key right;
    sf::Keyboard::Key rollLeft;
    sf::Keyboard::Key rollRight;
    sf::Keyboard::Key special_1;
    sf::Keyboard::Key special_2;
    sf::Keyboard::Key special_3;
    sf::Keyboard::Key special_4;

    sf::Mouse::Button primary;
    sf::Mouse::Button secondary;

    Chunk* target;
    sf::View view;
};

class ControlManager
{
public:
    ControlManager();
    virtual ~ControlManager();

    Player& getPlayer(const std::string& target);
    void choiceUpdate();
    void drawUpdate();
protected:
private:
    Universe& m_rUniverse;
    sf::RenderWindow& m_rWindow;

    std::vector<Player> m_localPlayerList;
    std::vector<Player> m_deactivatedPlayerList;//we dont do these
    ///std::vector<std::tr1::shared_ptr<SyntheticIntelligence> > m_localSIList;
};

#endif // CONTROLMANAGER_H
