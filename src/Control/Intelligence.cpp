#include "Intelligence.h"

Intelligence::Intelligence()
{
    //ctor
}

Intelligence::~Intelligence()
{
    //dtor
}

Chunk* Intelligence::getTarget()
{
    return m_target;
}
const Chunk* Intelligence::getTarget() const
{
    return m_target;
}

void Intelligence::setTarget(Chunk* target)
{
    m_target = target;
    m_hasControl = true;
}
void Intelligence::removeControl()
{
    m_target = NULL;
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
