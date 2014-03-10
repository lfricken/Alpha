#include "Intelligence.h"

Intelligence::Intelligence()
{
    m_pTarget = NULL;
    m_hasControl = false;
}

Intelligence::~Intelligence()
{
    if(m_hasControl)
        m_pTarget->forgetController();
}

Chunk* Intelligence::getTarget()
{
    return m_pTarget;
}
const Chunk* Intelligence::getTarget() const
{
    return m_pTarget;
}

void Intelligence::setTarget(Chunk* target)
{
    if(m_hasControl)
        m_pTarget->forgetController();

    m_pTarget = target;
    m_hasControl = true;
    m_pTarget->setController(this);
}
void Intelligence::removeControl()
{
    m_pTarget = NULL;
    m_hasControl = false;
}
bool Intelligence::getControlState() const
{
    return m_hasControl;
}
void Intelligence::setAim(const sf::Vector2f& newAim)
{
    m_aim = newAim;
}
const sf::Vector2f& Intelligence::getAim() const
{
    return m_aim;
}
