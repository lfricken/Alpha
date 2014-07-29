#include "Timer.h"
#include "globals.h"


///make animation work
///fix force field collision with eachother



Timer::Timer()
{
    m_lastElapsedTime = game.getGameUniverse().getTime();

    m_lastCountDownTime = game.getGameUniverse().getTime();
    m_countDownTime = 1.0f;
    m_countDownTimeRemain = m_countDownTime;
}
Timer::~Timer()
{

}
float Timer::getTime() const//time elapsed as seconds since universe was initialized
{
    return game.getGameUniverse().getTime();
}
float Timer::getTimeElapsed()//get time elapsed since we last called this function
{
    float oldTime = m_lastElapsedTime;
    m_lastElapsedTime = game.getGameUniverse().getTime();
    return m_lastElapsedTime - oldTime;
}
bool Timer::isTimeUp()
{
    m_countDownTimeRemain -= game.getGameUniverse().getTime() - m_lastCountDownTime;
    m_lastCountDownTime = game.getGameUniverse().getTime();
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
