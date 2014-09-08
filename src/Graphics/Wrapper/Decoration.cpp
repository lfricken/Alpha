#include "Decoration.hpp"
#include "globals.hpp"

Decoration::Decoration(const DecorationData& rData)
{
    m_pGfxDerived = dynamic_cast<GraphicsComponent*>(game.getGameUniverse().getGfxCompFactory().generate(rData.gfxCompData));
    m_pGfxComp = m_pGfxDerived;
}
Decoration::~Decoration()
{
    m_pGfxComp->free();
}
void Decoration::setAnimState(AnimationState state)
{
    m_pGfxDerived->setAnimState(state);
}
