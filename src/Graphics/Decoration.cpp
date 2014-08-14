#include "Decoration.hpp"
#include "globals.hpp"

Decoration::Decoration(const DecorationData& rData) : IOBase(static_cast<IOBaseData>(rData))
{
    m_pGfxComp = dynamic_cast<GraphicsComponent*>(game.getGameUniverse().getGfxCompFactory().generate(rData.gfxCompData));
}
Decoration::~Decoration()
{
    m_pGfxComp->free();
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
void Decoration::setRotation(float radiansCCW)//radiansCCW
{
    m_pGfxComp->setRotation(radiansCCW);//radiansCCW
}
void Decoration::setAnimState(AnimationState state)
{
    m_pGfxComp->setAnimState(state);
}
void Decoration::setVelocity(const b2Vec2& rVel)
{
    m_pGfxComp->setVelocity(rVel);
}
