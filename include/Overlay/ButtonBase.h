#ifndef BUTTONBASE_H
#define BUTTONBASE_H

#include "IOBase.h"

class ButtonBase : public IOBase
{
public:

    ButtonBase();
    virtual ~ButtonBase();

    virtual bool leftClicked(sf::Vector2f mouseCoord);//returns true if it got clicked and does its things
    virtual bool rightClicked(sf::Vector2f mouseCoord);
    virtual bool middleClicked(sf::Vector2f mouseCoord);
    virtual bool mouseOver(sf::Vector2f mouseCoord);

    virtual void setPixCoords(const sf::Vector2i& rPixCoords);
    virtual const sf::Vector2i& getPixCoords();

    virtual void draw();
protected:
    virtual void setTexDefault();
    virtual void setTexLeftClick();
    virtual void setTexRightClick();
    virtual void setTexMiddleClick();
    virtual void setTexMouseOver();
    virtual void setTexRectIndex(unsigned int index);

    sf::Vector2i m_pixCoords;
    sf::RenderWindow& m_rWindow;

    sf::Sprite m_sprite;
    std::string m_textureFile;
    std::vector<sf::IntRect> m_buttonTexStates;//texture rectangles indicated the positions of textures to display
private:
};

#endif // BUTTONBASE_H
