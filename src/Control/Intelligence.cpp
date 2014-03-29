#include "Intelligence.h"

Intelligence::Intelligence()
{
    IntelligenceData data;
    f_initialize(data);
}
Intelligence::Intelligence(const IntelligenceData& data) : IOBase(static_cast<IOBaseData>(data))
{
    f_initialize(data);
}
Intelligence::~Intelligence()
{
    breakControl();
}
void Intelligence::f_initialize(const IntelligenceData& data)
{
    m_pTarget = NULL;
    m_hasTarget = false;
    m_isSending = true;
    m_targetName = data.targetName;
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
    if(target != NULL)
        m_pTarget->f_setController(this);

}
void Intelligence::breakControl()//done
{
    if(m_hasTarget)
        m_pTarget->f_forgetController();

    f_forgetTarget();
}
bool Intelligence::toggleSending()//changes whether or not we will send commands
{
    m_isSending = !m_isSending;
    return m_isSending;
}
bool Intelligence::toggleSending(bool newState)//changes whether or not we will send commands
{
    m_isSending = newState;
    return m_isSending;
}
bool Intelligence::isSending() const
{
    return m_isSending;
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
void Intelligence::setTargetName(const std::string& target)
{
    m_targetName = target;
}
const std::string& Intelligence::getTargetName()
{
    return m_targetName;
}
