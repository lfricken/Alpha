#include "Intelligence.h"
#include "globals.h"

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
    for(auto it = m_HUDspElements.begin(); it != m_HUDspElements.end(); ++it)
        (*it)->setState(newState);

    m_playerState = newState;
}
IOBaseReturn Intelligence::input(IOBaseArgs)
{
    if(rCommand == "enable")
        enable();
    else if(rCommand == "disable")
        disable();
    else if(rCommand == "switchLink")
    {
        std::string targetName;
        rInput >> targetName;
        Chunk* pTarget = game.getGameUniverse().getPhysTarget(targetName);
        if(pTarget != NULL)
        {
            linkControl(pTarget);
        }
        else
        {
            std::cout << "\nERROR in switchLink";
            ///ERROR LOG
        }

    }
    else
    {
        ///ERROR LOG
        std::cout << "\nCommand [" << rCommand << "] was never found.";
    }
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

void Intelligence::setAim(const b2Vec2& newAim)
{
    m_aim = newAim;
}
const b2Vec2& Intelligence::getAim() const
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
