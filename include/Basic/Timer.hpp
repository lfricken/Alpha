#ifndef TIMER_H
#define TIMER_H

/**purpose: simple knowledge of how long it has been since a time was last requested from this timer**/
class Timer
{
public:
    Timer();
    virtual ~Timer();

    float getTime() const;//time elapsed as seconds since game was initialized
    float getTimeElapsed() const;//get time elapsed since we last called this function, this isn't actually const!!!

    bool isTimeUp() const;//asks whether the time is up
    void setCountDown(float countDown);//sets the countdownTime
    void restartCountDown();//starts, the current countdown time from whatever it is supposed to be
protected:
private:
    mutable float m_lastElapsedTime;

    float m_countDownTime;
    mutable float m_lastCountDownTime;
    mutable float m_countDownTimeRemain;
};

#endif // TIMER_H
