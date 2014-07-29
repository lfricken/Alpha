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


        /**ADD PANELS**/
        void add(std::tr1::shared_ptr<leon::Panel> panel);

        /**GET PANELS**/
        leon::Panel* getTarget(const std::string& target);//returns base pointer to target
        leon::Panel* getTarget(unsigned int targetID);

        /**OVERLAY MANAGER**/
        void enableAll();
        void disableAll();
        void showAll();
        void hideAll();
        tgui::Gui& getGui();

        /**GRAPHICS**/
        void draw();//draws everything thats active, just calls gui draw

        /**IO**/
        virtual IOBaseReturn input(IOBaseArgs);
    protected:

    private:
        tgui::Gui m_gui;//the TGUI gui that handles most things
        std::vector<std::tr1::shared_ptr<leon::Panel> > m_panelList;//all the Panels that can get displayed, each item can be active or inactive, if its active, it gets displayed.
};

#endif // OverlayManager_H
