#include "ButtonBase.h"
#include <globals.h>


using namespace std;



ButtonBase::ButtonBase() : m_rWindow(game.getGameWindow())
{

}
ButtonBase::~ButtonBase()
{

}
bool ButtonBase::leftClicked(sf::Vector2f mouseCoord)//unfinished
{
    if (m_sprite.getGlobalBounds().contains(mouseCoord))
    {
        setTexLeftClick();
        return true;
    }
    return false;
}
bool ButtonBase::rightClicked(sf::Vector2f mouseCoord)//unfinished
{
    if (m_sprite.getGlobalBounds().contains(mouseCoord))
    {
        setTexRightClick();
        return true;
    }
    return false;
}
bool ButtonBase::middleClicked(sf::Vector2f mouseCoord)//unfinished
{
    if (m_sprite.getGlobalBounds().contains(mouseCoord))
    {
        setTexMiddleClick();
        return true;
    }
    return false;
}
bool ButtonBase::mouseOver(sf::Vector2f mouseCoord)//unfinished
{
    if (m_sprite.getGlobalBounds().contains(mouseCoord))
    {
        setTexMouseOver();
        return true;
    }
    setTexDefault();
    return false;
}
void ButtonBase::draw()
{
    m_sprite.setPosition(m_rWindow.mapPixelToCoords(m_pixCoords));
    m_rWindow.draw(m_sprite);
}
void ButtonBase::setPixCoords(const sf::Vector2i& rPixCoords)
{
    m_pixCoords = rPixCoords;
}
const sf::Vector2i& ButtonBase::getPixCoords()
{
    return m_pixCoords;
}
void ButtonBase::setTexDefault()
{
    ///m_sprite.setTextureRect(m_buttonTexStates[0]);
}
void ButtonBase::setTexLeftClick()
{
    ///m_sprite.setTextureRect(m_buttonTexStates[1]);
}
void ButtonBase::setTexRightClick()
{
    ///m_sprite.setTextureRect(m_buttonTexStates[2]);
}
void ButtonBase::setTexMiddleClick()
{
    ///m_sprite.setTextureRect(m_buttonTexStates[3]);
}
void ButtonBase::setTexMouseOver()
{
    ///m_sprite.setTextureRect(m_buttonTexStates[4]);
}
void ButtonBase::setTexRectIndex(unsigned int index)
{
    ///m_sprite.setTextureRect(m_buttonTexStates[index]);
}
