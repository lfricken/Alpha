#include "Spinner.hpp"
#include "stdafx.hpp"
#include "Convert.hpp"

Spinner::Spinner(const SpinnerData& rData)
{
    m_pGfxDerived = dynamic_cast<GraphicsComponent*>(game.getGameUniverse().getGfxCompFactory().generate(rData.gfxCompData));
    m_pGfxComp = m_pGfxDerived;

    m_isEnabled = rData.startsSpinning;
    m_spinnerAxisOffset = rData.spinnerOffset;
    m_spinRate = leon::degToRad(rData.spinRate);

    if(rData.randomInitRotation)
        m_currentRelativeRotation = leon::degToRad( rand()%360 );
    else
        m_currentRelativeRotation = rData.startRotation;
}
Spinner::~Spinner()
{
    m_pGfxComp->free();
}
void Spinner::setAnimState(AnimationState state)
{
    m_pGfxDerived->setAnimState(state);
}
void Spinner::setEnabled(bool enabled)
{
    m_isEnabled = enabled;
}
void Spinner::setRotation(float radiansCCW)//radiansCCW
{
    if(m_isEnabled)
        m_currentRelativeRotation += m_spinRate*m_timer.getTimeElapsed();

    m_pGfxDerived->setRotation(m_currentRelativeRotation+radiansCCW);
}
