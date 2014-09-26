#include "Spinner.hpp"
#include "stdafx.hpp"
#include "Convert.hpp"

Spinner::Spinner(const SpinnerData& rData)
{
    m_pGfxDerived = dynamic_cast<GraphicsComponent*>(game.getGameUniverse().getGfxCompFactory().generate(rData.gfxCompData));
    m_pGfxComp = m_pGfxDerived;

    m_isEnabled = rData.startsSpinning;
    m_spinnerAxisOffset = rData.spinnerOffset; ///how far away are we from the center of the module HAS NOT BEEN IMPLMENETED

    m_accel = leon::degToRad(rData.accel);
    m_decel = leon::degToRad(rData.decel);
    m_maxRate = leon::degToRad(rData.maxRate);
    m_minRate = leon::degToRad(rData.minRate);
    m_currentRate = m_minRate;

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
    float time = m_timer.getTimeElapsed();
    if(m_isEnabled)
    {
        if(m_currentRate < m_minRate)//if we are slower than max, speed up to that
        {
            m_currentRate += m_accel*time;
        }
        else if(m_accelThisTick)//accel to max
        {
            m_currentRate += m_accel*time;
            if(m_currentRate > m_maxRate)
                m_currentRate = m_maxRate;
        }
        else//decel to min
        {
            m_currentRate += m_decel*time;
            if(m_currentRate < m_minRate)
                m_currentRate = m_minRate;
        }
    }
    else//decel to 0
    {
        m_currentRate += m_decel*time;
        if(m_currentRate<0)//prevent reversal when off
            m_currentRate = 0;
    }
    m_currentRelativeRotation += m_currentRate*time;
    m_pGfxDerived->setRotation(m_currentRelativeRotation+radiansCCW);
    m_accelThisTick = false;
}
void Spinner::spinup()
{
    m_accelThisTick = true;
}
