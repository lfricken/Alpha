#ifndef GRAPHICSWRAPPERINTERFACE_H
#define GRAPHICSWRAPPERINTERFACE_H

#include "stdafx.hpp"
#include "AnimationSetting.hpp"

class BaseGraphicsComponent;

class GraphicsWrapperInterface/**PURE VIRTUAL**/
{
public:
    GraphicsWrapperInterface();
    virtual ~GraphicsWrapperInterface();

    virtual void setPosition(const b2Vec2& rPos);
    virtual void setRotation(float radiansCCW);//RADIANS CCW
    virtual void setVelocity(const b2Vec2& rVel);
    virtual void setColor(const sf::Color& rColor);

    virtual void setAnimState(AnimationState state) = 0;
protected:
    BaseGraphicsComponent* m_pGfxComp;

private:
};

#endif // GRAPHICSWRAPPERINTERFACE_H
