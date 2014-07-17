#include "AnimationLooper.h"

using namespace std;

AnimationLooper::AnimationLooper()
{
    m_accumulatedTime = 0;
    m_delay = 1;
    m_stopped = false;
    m_runOnce = false;

    m_sequence.push_back(sf::Vector2f(0,0));

    m_it = m_sequence.begin();
    m_itLast = m_it;
}
AnimationLooper::~AnimationLooper()
{

}
void AnimationLooper::runOnce(bool once)
{
    m_runOnce = once;
}
void AnimationLooper::restart()//starts from beginning
{
    m_accumulatedTime = 0;
    m_it = m_sequence.begin();
    m_itLast = m_it;

    start();
}
void AnimationLooper::start()//starts the animation loop from current positions
{
    m_timer.getTimeElapsed();//reset the clock so it continues from this moment
    m_stopped = false;
}
void AnimationLooper::stop()//stops the animation loop
{
    m_accumulatedTime += m_timer.getTimeElapsed();//store how close we were to another frame
    m_stopped = true;
}
void AnimationLooper::setDelay(float delay)//delay to set the timer
{
    m_delay = delay;//time between each frame
}
void AnimationLooper::setSequence(const std::vector<sf::Vector2f>& sequence)//sequence of tiles to loop through
{
    m_sequence = sequence;
    m_it = m_sequence.begin();
    m_itLast = m_it;
}
const sf::Vector2f& AnimationLooper::getTile()//get the current tile we should be on
{
    if(!m_stopped)
    {
        for(m_accumulatedTime += m_timer.getTimeElapsed(); m_accumulatedTime >= m_delay; m_accumulatedTime -= m_delay)
        {
            m_itLast = f_getNext();
        }
    }
    return *m_itLast;
}
AnimationLooper::const_it AnimationLooper::f_getNext()
{
    ++m_it;
    if(m_it == m_sequence.end())//if we have reached the end, and we aren't supposed to run once, restart
    {
        if(m_runOnce)
            return --m_it;
        else
            return m_it = m_sequence.begin();
    }
    else
        return m_it;
}
