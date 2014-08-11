#ifndef SPINNER_H
#define SPINNER_H

#include "Decoration.hpp"

class GModule;

struct SpinnerData
{
    SpinnerData():
        startRotation(0),
        spinnerOffset(0,0),
        spinRate(90),
        decorData()
    {
        decorData.gfxCompData.gfxLayer = GraphicsLayer::ShipAppendagesUpper;
        decorData.gfxCompData.scale = sf::Vector2f(0.5, 0.5);
        decorData.gfxCompData.texName = "textures/radar/dish.png";
        decorData.gfxCompData.animationFileName = "textures/radar/dish.acfg";
    }
    float startRotation;//degrees CCW
    b2Vec2 spinnerOffset;//offset of sprite and spin from center of Module
    float spinRate;// degrees/second CCW
    DecorationData decorData;
};


class Spinner
{
public:
    Spinner(const SpinnerData& rData);
    virtual ~Spinner();

    void update(const b2Vec2& rCenterOfParent, float radiansCCW);//use time

protected:
private:

    b2Vec2 m_spinnerAxisOffset;//how far away are we from the center of the module
    float m_spinRate;// radians/second CCW
    float m_currentRelativeRotation;//how much are we rotated compared to the body
    Timer m_timer;

    Decoration m_decor;
};

#endif // SPINNER_H
