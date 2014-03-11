#include "Intelligence.h"

Intelligence::Intelligence()
{
    m_pTarget = NULL;
    m_hasTarget = false;
}

Intelligence::~Intelligence()
{
    breakControl();
}

/**CONTROL**/
Chunk* Intelligence::getTarget() const//done
{
    return m_pTarget;
}
bool Intelligence::hasTarget() const//done
{
    return m_hasTarget;
}
void Intelligence::linkControl(Chunk* target)
{
    f_setTarget(target);
    m_pTarget->f_setController(this);
}
void Intelligence::breakControl()//done
{
    if(m_hasTarget)
        m_pTarget->f_forgetController();

    f_forgetTarget();
}
void Intelligence::f_forgetTarget()//done
{
    m_pTarget = NULL;
    m_hasTarget = false;
}
void Intelligence::f_setTarget(Chunk* target)//done
{
    breakControl();
    m_pTarget = target;
    m_hasTarget = true;
}
/**END**/

void Intelligence::setAim(const sf::Vector2f& newAim)
{
    m_aim = newAim;
}
const sf::Vector2f& Intelligence::getAim() const
{
    return m_aim;
}
