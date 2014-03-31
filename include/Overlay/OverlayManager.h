#ifndef OVERLAYMANAGER_H
#define OVERLAYMANAGER_H

#include "stdafx.h"
#include "Panel.h"

///Make an onChange() event output, so player would have OnHealthChange "healthMonitor" update(send its info in parameter)

class OverlayManager : public IOBase//Overlay Manager holds overlays. Each overlay can have stuff on it that can be clicked,
//but only if that overlay is active, otherwise it cannot be clicked, and is not displayed
{
    public:
        OverlayManager(sf::RenderWindow& window);
        ~OverlayManager();

        void setActive(const std::string& target);//sets the target overlay active(taking input)
        void setInactive(const std::string& target);//sets target overlay inactive(not taking input)
        void show(const std::string& target);//sets the target overlay to showing
        void hide(const std::string& target);

        void toggleActive(const std::string& target);//toggles the activity of an overlay
        void toggleShow(const std::string& target);

        void deactivateAll();//deactivate all Overlays
        void activateAll();
        void showAll();
        void hideAll();

        void add(std::tr1::shared_ptr<leon::Panel> panel);

        tgui::Gui& getGui();

        IOBase* getTarget(const std::string& target);//returns base pointer to target
        IOBase* getTarget(unsigned int target);

        void draw();//draws everything thats active, just calls gui draw

    protected:

    private:
        tgui::Gui m_gui;
        std::vector<std::tr1::shared_ptr<leon::Panel> > m_panelList;//all the Overlays that can get displayed, each item can be active or inactive, if its active, it gets displayed.
};

#endif // OverlayManager_H
