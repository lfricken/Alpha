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
        accel(90),// degrees/second CCW
        decel(-50),// degrees/second CCW
        maxRate(360),// degrees/second CCW
        minRate(10)// degrees/second CCW
    {
        gfxCompData.gfxLayer = GraphicsLayer::ShipAppendagesUpper;
        gfxCompData.dimensions = sf::Vector2f(128, 128);
        gfxCompData.texName = "textures/radar/dish.png";
        gfxCompData.animationFileName = "textures/radar/dish.acfg";
    }
    bool startsSpinning;
    bool randomInitRotation;
    float startRotation;//degrees CCW
    b2Vec2 spinnerOffset;///offset of sprite and spin from center of Module  ///how far away are we from the center of the module HAS NOT BEEN IMPLMENETED

    float accel;// degrees/second CCW
    float decel;// degrees/second CCW
    float maxRate;// degrees/second CCW
    float minRate;// degrees/second CCW

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

    void spinup();//accelerate this tick, if this isn't called, we decelerate
protected:
private:
    float m_accel;//spinup accel
    float m_decel;//if we dont accel we decel
    float m_maxRate;//the max spin/s we can have
    float m_minRate;// radians/second CCW we will try and achieve this rate
    float m_currentRate;//our current speed
    bool m_accelThisTick;//if true, we should accelerate with accel up to max rate, if false, use decel to m_spinRate

    b2Vec2 m_spinnerAxisOffset;///how far away are we from the center of the module HAS NOT BEEN IMPLMENETED
    float m_currentRelativeRotation;//how much are we rotated compared to the body
    Timer m_timer;

    bool m_isEnabled;
    GraphicsComponent* m_pGfxDerived;
};

#endif // SPINNER_H
