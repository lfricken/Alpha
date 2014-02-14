#ifndef OVERLAY_H
#define OVERLAY_H

#include <MultipleInheritance/IOBase.h>
#include <Overlay/Panel.h>

class Overlay : public IOBase//an overlay can have panels, which are just collections of buttons
{
public:
    Overlay();
    ~Overlay();

    void setActive(bool active);//change our active state
    bool getActive();//find the current active state
    bool toggleActive();//switch our active state, and return our new state

    void setDisplayPriority(int priority);
    int getDisplayPriority();
    void add(Panel& rPanel);//add a copy of this pannel to the list of panels in this overlay

    IOBase* getTarget(std::string target);//returns a pointer to the target object

    bool leftClicked(sf::Vector2f mouseCoord);
    bool rightClicked(sf::Vector2f mouseCoord);
    bool middleClicked(sf::Vector2f mouseCoord);//if contain the click, return true, otherwise false
    bool mouseOver(sf::Vector2f mouseCoord);//implement some sort of panel drag ability!!!

    void draw();//loop over our panels and call their draws
protected:

private:
    std::vector<Panel> m_panelsList;//list of panels on this overlay
    bool m_isActive;//is this panel active or not
    int m_displayPriority;//higher numberse mean higher priority, so 1000 will get displayed on top of 999, so if two overlays are active, higher pri will get clicked first and displayed on top
};

#endif // OVERLAY_H
