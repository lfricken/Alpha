#ifndef TIMER_H
#define TIMER_H

/**purpose: simple knowledge of how long it has been since a time was last requested from this timer**/
class Timer
{
public:
    Timer();
    virtual ~Timer();

    float getTime() const;//time elapsed as seconds since game was initialized
    float getTimeElapsed() const;//get time elapsed since we last called this function

    bool isTimeUp() const;//asks whether the time is up
    void resetTimer();
    void setCountDown(float countDown);
    void restartCountDown();
protected:
private:
    mutable float m_lastElapsedTime;

    float m_countDownTime;
    mutable float m_lastCountDownTime;
    mutable float m_countDownTimeRemain;
};

#endif // TIMER_H
