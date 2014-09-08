#ifndef SPINNER_H
#define SPINNER_H

#include "GraphicsComponent.hpp"
#include "GraphicsWrapperInterface.hpp"

struct SpinnerData
{
    SpinnerData():
        gfxCompData(),
        startsSpinning(true),
        randomInitRotation(true),
        startRotation(0),
        spinnerOffset(0,0),
        spinRate(90)
    {
        gfxCompData.gfxLayer = GraphicsLayer::ShipAppendagesUpper;
        gfxCompData.scale = sf::Vector2f(0.5, 0.5);
        gfxCompData.texName = "textures/radar/dish.png";
        gfxCompData.animationFileName = "textures/radar/dish.acfg";
    }
    bool startsSpinning;
    bool randomInitRotation;
    float startRotation;//degrees CCW
    b2Vec2 spinnerOffset;//offset of sprite and spin from center of Module
    float spinRate;// degrees/second CCW
    GraphicsComponentData gfxCompData;
};


class Spinner : public GraphicsWrapperInterface
{
public:
    Spinner(const SpinnerData& rData);
    virtual ~Spinner();

    void setAnimState(AnimationState state);
    void setEnabled(bool enabled);
    void setRotation(float radiansCCW);

protected:
private:
    b2Vec2 m_spinnerAxisOffset;//how far away are we from the center of the module
    float m_spinRate;// radians/second CCW
    float m_currentRelativeRotation;//how much are we rotated compared to the body
    Timer m_timer;

    bool m_isEnabled;
    GraphicsComponent* m_pGfxDerived;
};

#endif // SPINNER_H
