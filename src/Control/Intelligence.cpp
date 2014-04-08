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
    m_playerState = PlayerState::Playing;
    m_HUDspElements = data.hudSPelements;
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
PlayerState Intelligence::getState() const
{
    return m_playerState;
}
void Intelligence::setState(PlayerState newState)
{
    typedef std::vector<std::tr1::shared_ptr<leon::Panel> >::iterator type;
    if(newState == PlayerState::Editing)/**the new state is editing**/
    {
 ///       for(type it = m_HUDspElements.begin(); it != m_HUDspElements.end(); ++it)
///            (*it)->setState(newState);
    }
    else if(m_playerState == Editing)/**we must be going out of edit mode**/
    {
  ///      for(type it = m_HUDspElements.begin(); it != m_HUDspElements.end(); ++it)
   ///         (*it)->setState(newState);
    }

    m_playerState = newState;
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
