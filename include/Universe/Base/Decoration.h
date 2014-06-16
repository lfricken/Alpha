#ifndef DECORATION_H
#define DECORATION_H

#include "IOBase.h"
#include "GraphicsComponent.h"

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
    Decoration();
    Decoration(const DecorationData& rData);
    virtual ~Decoration();

    const GraphicsComponent& getGfxComp() const;

    void setPosition(const sf::Vector2f& pos);
    void setRotation(float r);
    void setAnimState(AnimationState state);

    void update();//update animation on our graphicsComponent

protected:
private:
    virtual void f_init(const DecorationData& rData);

    GraphicsComponent m_gfxComp;
};

#endif // DECORATION_H
