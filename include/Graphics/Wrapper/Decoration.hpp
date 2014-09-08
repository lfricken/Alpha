#ifndef DECORATION_H
#define DECORATION_H

#include "GraphicsWrapperInterface.hpp"
#include "GraphicsComponent.hpp"

struct DecorationData
{
    DecorationData() :
        gfxCompData()
    {
    }

    GraphicsComponentData gfxCompData;
};

class Decoration : public GraphicsWrapperInterface
{
public:
    Decoration(const DecorationData& rData);
    virtual ~Decoration();

    void setAnimState(AnimationState state);

protected:
private:

    GraphicsComponent* m_pGfxDerived;
};

#endif // DECORATION_H
