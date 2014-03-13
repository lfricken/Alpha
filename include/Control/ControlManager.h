#ifndef CONTROLMANAGER_H
#define CONTROLMANAGER_H

#include "stdafx.h"
#include "Universe.h"
#include "Player.h"

class ControlManager
{
public:
    ControlManager();
    virtual ~ControlManager();

    Player& getPlayer(const std::string& target);
    int choiceUpdate();
    void drawUpdate();
protected:
private:
    void f_cheats(std::vector<Player>::iterator it);

    Universe& m_rUniverse;
    sf::RenderWindow& m_rWindow;
    sf::Event m_event;

    std::vector<Player> m_localPlayerList;
    std::vector<Player> m_deactivatedPlayerList;///we dont do these, what is this for????
    ///std::vector<std::tr1::shared_ptr<SyntheticIntelligence> > m_localSIList;
};

#endif // CONTROLMANAGER_H
