#include "Decoration.hpp"
#include "globals.hpp"

Decoration::Decoration()
{
    DecorationData data;
    f_init(data);
}
Decoration::Decoration(const DecorationData& rData)
{
    f_init(rData);
}
Decoration::~Decoration()
{
    m_pGfxComp->free();
}
void Decoration::f_init(const DecorationData& rData)
{
    m_pGfxComp = game.getGameUniverse().getGfxCompFactory().generate(rData.gfxCompData);
}
/*
const GraphicsComponent& Decoration::getGfxComp() const
{
    return *m_pGfxComp;
}*/
void Decoration::setPosition(const b2Vec2& rPos)
{
    m_pGfxComp->setPosition(rPos);
}
void Decoration::setRotation(float radians)//radians
{
    m_pGfxComp->setRotation(radians);//radians
}
void Decoration::setAnimState(AnimationState state)
{
    m_pGfxComp->setAnimState(state);
}
