#include "Intelligence.hpp"
#include "globals.hpp"

Intelligence::Intelligence(const IntelligenceData& rData) : IOBase(rData), m_linker(this)
{
    m_playerState = PlayerState::Interfacing;
    m_HUDspElements = rData.hudSPelements;
    m_targetName = rData.targetName;
}
Intelligence::~Intelligence()
{
    m_linker.breakLink();
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
const b2Vec2& Intelligence::getAim() const///needs to recalculate
{
    return m_aim;
}

const std::string& Intelligence::getTargetName() const
{
    return m_targetName;
}
