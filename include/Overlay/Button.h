#ifndef BUTTON_H
#define BUTTON_H

#include "ButtonBase.h"

class Button : public ButtonBase
{
public:
    Button();
    ~Button();


    void setPanelCoords(const sf::Vector2f& rPanelCoords);
    const sf::Vector2f& getPanelCoords() const;


protected:
private:

    sf::Vector2f m_panelCoords;//position relative to the panel we're in, so basically add these to the panels coordinates when displaying
};

#endif // BUTTON_H
