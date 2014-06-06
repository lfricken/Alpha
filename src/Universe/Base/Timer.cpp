#include "Timer.h"
#include "globals.h"

Timer::Timer()
{
    m_lastCountDownTime = m_lastElapsedTime = game.getTime();
    m_countDownTime = 1.0f;
    m_countDownTimeRemain = m_countDownTime;
}
Timer::~Timer()
{
    //dtor
}
float Timer::getTime() const//time elapsed as seconds since game was initialized
{
    return game.getTime();
}
float Timer::getTimeElapsed()//get time elapsed since we last called this function
{
    float temp = m_lastElapsedTime;
    m_lastElapsedTime = game.getTime();
    return m_lastElapsedTime - temp;
}
bool Timer::isTimeUp()
{
    m_countDownTimeRemain -= game.getTime() - m_lastCountDownTime;
    m_lastCountDownTime = game.getTime();
    if(m_countDownTimeRemain <= 0)
    {
        m_countDownTimeRemain = m_countDownTime;
        return true;
    }
    else
        return false;
}
void Timer::setCountDown(float countDown)
{
    m_countDownTime = countDown;
}
void Timer::restartCountDown()
{
    m_countDownTimeRemain = m_countDownTime;
}
