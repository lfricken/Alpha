#include "Needle.hpp"

#include "Rotation.hpp"

using namespace leon;

Needle::Needle(const NeedleData& rData)
{
    m_pGfxDerived = dynamic_cast<GraphicsComponent*>(game.getGameUniverse().getGfxCompFactory().generate(rData.gfxCompData));
    m_pGfxComp = m_pGfxDerived;

    m_changeVel = degToRad(rData.changeVel);
    m_returnVel = degToRad(rData.returnVel);
    m_currentRate = 0;

    m_relRot = 0;
    m_desiredRot = 0;
    m_defaultRot = degToRad(rData.defaultRot);

    m_maxLimit = degToRad(rData.maxRot);
    m_minLimit = degToRad(rData.minRot);

    m_resets = rData.resets;
    m_return = false;
    m_isEnabled = rData.startsEnabled;
}
Needle::~Needle()
{
    m_pGfxComp->free();
}
void Needle::changeDesiredPosition(float radiansCCW)//radians CCW
{
    m_desiredRot = radiansCCW;
    if(m_relRot < radiansCCW)//if radial is less than desired position
        m_currentRate = m_changeVel;
    else//radial is greater than desired position
        m_currentRate = -m_changeVel;
    m_return = false;
}
void Needle::setRotation(float radiansCCW)
{
    if(m_return)
    {
        if(m_relRot > m_defaultRot)
            m_currentRate = -m_returnVel;
        else if(m_relRot < m_defaultRot)
            m_currentRate = m_returnVel;
        else
            m_currentRate = 0;
    }
    if(m_isEnabled)
    {
        const float time = m_timer.getTimeElapsed();
        const float relRotOld = m_relRot;
        m_relRot += m_currentRate*time;
        bool isNeg = false;

        if(m_currentRate < 0)
            isNeg = true;
        if(!isNeg && m_relRot >= m_desiredRot && relRotOld <= m_desiredRot)
            m_relRot = m_desiredRot;
        else if(isNeg && m_relRot <= m_desiredRot && relRotOld >= m_desiredRot)
            m_relRot = m_desiredRot;
    }

    if(m_relRot > m_maxLimit)
        m_relRot = m_maxLimit;
    else if(m_relRot < m_minLimit)
        m_relRot = m_minLimit;
    m_pGfxDerived->setRotation(m_relRot+radiansCCW);

    m_return = true;
    if(m_resets)
        m_desiredRot = m_defaultRot;
}
void Needle::setEnabled(bool enabled)
{
    m_isEnabled = enabled;
}
void Needle::setAnimState(AnimationState state)
{
    m_pGfxDerived->setAnimState(state);
}
void Needle::setNeedleSpeed(float degsPerSec)//degrees per second!
{
    m_changeVel = degToRad(degsPerSec);
}
