#ifndef DECORATION_H
#define DECORATION_H

#include "IOBase.hpp"
#include "GraphicsComponent.hpp"

struct DecorationData : public IOBaseData
{
    DecorationData() :
        IOBaseData(),
        gfxCompData()
    {
        type = ClassType::DECORATION;
    }

    GraphicsComponentData gfxCompData;
};

class Decoration : public IOBase
{
public:
    Decoration(const DecorationData& rData);
    virtual ~Decoration();

    void setPosition(const b2Vec2& rPos);
    void setRotation(float radiansCCW);//RADIANS CCW
    void setAnimState(AnimationState state);
    void setVelocity(const b2Vec2& rVel);

protected:
private:

    GraphicsComponent* m_pGfxComp;
};

#endif // DECORATION_H
