#include "AnimationLooper.h"

AnimationLooper::AnimationLooper()
{
    m_stopped = false;
}

AnimationLooper::~AnimationLooper()
{
    //dtor
}
void AnimationLooper::restart()//starts from beginning
{
    m_timer.restartCountDown();//helps control time delay between each animation frame
    m_timer.getTimeElapsed();

    m_lastSwitchTime = m_timer.getTime();//stores the last time we changed our texture tile
    m_accumulatedTime = 0;//stores residual time left over from a switch, like 0.01 seconds.
    m_stopped = false;

    m_it = m_sequence.begin();
}
bool AnimationLooper::start()//starts the animation loop, returns true if it was in stop mode
{

}
bool AnimationLooper::stop()//stops the animation loop, returns true if it wasn't already stopped
{

}
void AnimationLooper::setDelay(float delay)//delay to set the timer
{

}
void AnimationLooper::setSequence(const std::vector<sf::Vector2f>& sequence)//sequence of tiles to loop through
{

}
const sf::Vector2f& AnimationLooper::getTile()//get the current tile we should be on
{

}
