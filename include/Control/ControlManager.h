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
    Intelligence* getIntelligence(unsigned int targetID);
    Player* getPlayer(const std::string& target);
    Player* getPlayer(unsigned int targetID);
    ///also get SI;

    void add(std::tr1::shared_ptr<Player> spPlayer);
    ///also add SI;

    void setupControl();
    int choiceUpdate(sf::Event& rEvent);
    int pressedUpdate();
    void drawUpdate();
protected:
private:
    void f_cheats(std::vector<std::tr1::shared_ptr<Player> >::iterator it, sf::Event& rEvent);
    tgui::Widget::Ptr f_MouseOnWhichWidget(float x, float y, std::vector<tgui::Widget::Ptr>& widgets);

    std::vector<std::tr1::shared_ptr<Player> > m_localPlayerList;
    ///std::vector<std::tr1::shared_ptr<SyntheticIntelligence> > m_localSIList;
};

#endif // CONTROLMANAGER_H
