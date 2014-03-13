#ifndef OVERLAYMANAGER_H
#define OVERLAYMANAGER_H

#include "stdafx.h"
#include "IOBase.h"
#include "Overlay.h"

///Make an onChange() event output, so player would have OnHealthChange "healthMonitor" update(send its info in parameter)

class OverlayManager : public IOBase//Overlay Manager holds overlays. Each overlay can have stuff on it that can be clicked,
//but only if that overlay is active, otherwise it cannot be clicked, and is not displayed
{
    public:
        OverlayManager();
        ~OverlayManager();

        void setActive(std::string target);//sets the target overlay active
        void setInactive(std::string target);

        void toggleActive(std::string target);//toggles the activity of an overlay
        void deactivateAll();//deactivate all Overlays

        ///void load(std::string filename);//load Overlays from a file and ADD it to the set of Overlays
        ///void remove(std::string target);

        IOBase* getTarget(std::string target);//returns base pointer to target
        void draw();//draws everything thats active

    protected:

    private:
        std::vector<Overlay> m_overlayList;//all the Overlays that can get displayed, each item can be active or inactive, if its active, it gets displayed.
};

#endif // OverlayManager_H
