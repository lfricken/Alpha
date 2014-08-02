#include "Intelligence.hpp"
#include "globals.hpp"

Intelligence::Intelligence() : IOBase(), m_linker(this)
{
    IntelligenceData data;
    f_initialize(data);
}
Intelligence::Intelligence(const IntelligenceData& data) : IOBase(static_cast<IOBaseData>(data)), m_linker(this)
{
    f_initialize(data);
}
Intelligence::~Intelligence()
{
    m_linker.breakLink();
}
void Intelligence::f_initialize(const IntelligenceData& data)
{
    m_playerState = PlayerState::Playing;
    m_HUDspElements = data.hudSPelements;
    m_targetName = data.targetName;
}
/**CONTROL**/
Link<Intelligence, Chunk>& Intelligence::getLinker()
{
    return m_linker;
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
            m_linker.link(&pTarget->getLinker());
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
/**END**/

void Intelligence::setAim(const b2Vec2& newAim)
{
    m_aim = newAim;
}
const b2Vec2& Intelligence::getAim() const
{
    return m_aim;
}

const std::string& Intelligence::getTargetName() const
{
    return m_targetName;
}
