#include "Intelligence.h"

Intelligence::Intelligence()
{
    //ctor
}

Intelligence::~Intelligence()
{
    //dtor
}
void Intelligence::setTarget()
{
    ///take control of target
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
const sf::Vector2f& Intelligence::getAim() const
{
    return m_aim;
}
