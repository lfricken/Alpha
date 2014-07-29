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

    ///remove anything here that isn't a state we hold
    Intelligence* m_pCIT;//control intelligence target
    Player* m_pCPT;//control player target

    b2Body* m_bodyTarget;


    tgui::Widget::Ptr m_pDraggingWidget;//target that is getting dragged
    sf::Vector2f m_pDraggingPosition;//position of the dragging

    std::vector<std::tr1::shared_ptr<Player> > m_localPlayerList;
    std::vector<Player> m_deactivatedPlayerList;///we dont do these, what is this for????
    ///std::vector<std::tr1::shared_ptr<SyntheticIntelligence> > m_localSIList;
};

#endif // CONTROLMANAGER_H
