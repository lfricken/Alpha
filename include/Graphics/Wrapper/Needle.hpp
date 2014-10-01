#ifndef NEEDLE_HPP
#define NEEDLE_HPP

#include "GraphicsComponent.hpp"
#include "GraphicsWrapperInterface.hpp"

struct NeedleData
{
    NeedleData():
        gfxCompData(),
        changeVel(135),
        returnVel(45),
        defaultRot(0),
        maxRot(180),
        minRot(-180),
        resets(true),
        startsEnabled(true)
        {
            gfxCompData.gfxLayer = GraphicsLayer::ShipAppendagesUpper;
        }

    float changeVel;//degrees/s
    float returnVel;//degrees/s

    float defaultRot;//degrees

    float maxRot;//degrees
    float minRot;//degrees
    bool resets;
    bool startsEnabled;
    GraphicsComponentData gfxCompData;
};

class Needle : public GraphicsWrapperInterface
{
public:
    Needle(const NeedleData& rData);
    virtual ~Needle();

    void changeDesiredPosition(float radiansCCW);//radians CCW
    void setEnabled(bool enabled);
    void setRotation(float radiansCCW);
    void setAnimState(AnimationState state);

    void setNeedleSpeed(float degsPerSec);//degrees per second!
protected:
private:
    float m_changeVel;//when we are told to adjust left or right, how much
    float m_returnVel;//how quickly do we try and return to default
    float m_currentRate;

    float m_relRot;
    float m_desiredRot;
    float m_defaultRot;

    float m_maxLimit;//radians CCW
    float m_minLimit;//radians CCW

    Timer m_timer;
    bool m_resets;
    bool m_return;
    bool m_isEnabled;
    GraphicsComponent* m_pGfxDerived;
};

#endif // NEEDLE_HPP
