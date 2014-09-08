#include "RadialMeter.hpp"
#include "globals.hpp"

RadialMeter::RadialMeter(const RadialMeterData& rData)
{
    m_pGfxDerived = dynamic_cast<TriangleFan*>(game.getGameUniverse().getGfxCompFactory().generate(rData.gfxCompData));
    m_pGfxComp = m_pGfxDerived;
}
RadialMeter::~RadialMeter()
{
    m_pGfxComp->free();
}
void RadialMeter::setPercentFull(float percent)//0-100
{
    m_pGfxDerived->setTextureRotation(0.01*percent*2*pi);//0.01 because the percent needs to range from 0 to 1 to modify the 2pi angle to a fraction
}
void RadialMeter::setAnimState(AnimationState state)
{

}
