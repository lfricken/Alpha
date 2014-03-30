#ifndef CONTROLMANAGER_H
#define CONTROLMANAGER_H

#include "stdafx.h"
#include "Universe.h"
#include "Player.h"

class ControlManager
{
public:
    ControlManager();;
    virtual ~ControlManager();

    Intelligence* getIntelligence(const std::string& target);
    Player* getPlayer(const std::string& target);
    ///also get SI;

    void add(const PlayerData& data);
    ///also add SI;

    void setupControl();
    int choiceUpdate(sf::Event& rEvent);
    int pressedUpdate();
    void drawUpdate();
protected:
private:
    void f_cheats(std::vector<std::tr1::shared_ptr<Player> >::iterator it, sf::Event& rEvent);

    Intelligence* m_pCIT;
    Player* m_pCPT;
    Universe& m_rUniverse;
    sf::RenderWindow& m_rWindow;
    tgui::Gui& m_rGui;
    b2Body* m_bodyTarget;
    Chunk* m_chunkTarget;

    std::vector<std::tr1::shared_ptr<Player> > m_localPlayerList;
    std::vector<Player> m_deactivatedPlayerList;///we dont do these, what is this for????
    ///std::vector<std::tr1::shared_ptr<SyntheticIntelligence> > m_localSIList;
};

#endif // CONTROLMANAGER_H
