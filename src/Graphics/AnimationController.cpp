#include "AnimationController.hpp"
#include "globals.hpp"

AnimationController::AnimationController()
{
    m_pSettingsList = NULL;

    m_currentIndex = 0;
    m_accumulatedTime = 0;
    m_timer.getTimeElapsed();
}
AnimationController::~AnimationController()
{

}
void AnimationController::load(const std::string& animationFile)
{
    m_pSettingsList = game.getAnimationAllocator().requestPtr(animationFile);
    setState("Default");
}

    const std::string& AnimationController::getState() const
    {
        return m_state;
    }

void AnimationController::setState(const AnimationState& state)
{
    m_state = state;
    auto it = m_pSettingsList->find(state);

    if(it == m_pSettingsList->cend())
    {
        it = m_pSettingsList->find("Error");
        if(it != m_pSettingsList->cend())
            m_pCurrentSetting = &(it->second);
        else
            std::cout << "\n[" << state << "] " << FILELINE;
    }
    else
        m_pCurrentSetting = &it->second;

    restart();
}
void AnimationController::restart()
{
    m_currentIndex = 0;
    m_accumulatedTime = 0;
    m_timer.getTimeElapsed();
}
const sf::Vector2f& AnimationController::getTile()
{
    f_update();
    return m_pCurrentSetting->sequence[m_currentIndex];
}
const sf::Vector2f& AnimationController::getTexTileSize() const
{
    return m_pCurrentSetting->texTileSize;
}
void AnimationController::f_update()
{
    m_accumulatedTime += m_timer.getTimeElapsed();
    bool done = false;
    while(not done)
    {
        int numTiles = m_pCurrentSetting->sequence.size();

        while((m_accumulatedTime > m_pCurrentSetting->delay) and (m_currentIndex < (numTiles-1)))
        {
            m_accumulatedTime-=m_pCurrentSetting->delay;
            ++m_currentIndex;
        }


        if(m_accumulatedTime > m_pCurrentSetting->delay)
        {
            if(m_pCurrentSetting->nextState == "")
                done = true;
            else
            {
                m_currentIndex = 0;
                m_accumulatedTime-=m_pCurrentSetting->delay;
                setState(m_pCurrentSetting->nextState);
            }
        }
        else
            done = true;
    }
}
