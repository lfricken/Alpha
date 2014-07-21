#ifndef TIMER_H
#define TIMER_H

/**purpose: simple knowledge of how long it has been since a time was last requested from this timer**/
class Timer
{
    public:
        Timer();
        virtual ~Timer();

        float getTime() const;//time elapsed as seconds since game was initialized
        float getTimeElapsed();//get time elapsed since we last called this function

        bool isTimeUp();//asks whether the time is up, if it is, reset
        void setCountDown(float countDown);
        void restartCountDown();
    protected:
    private:
        float m_lastElapsedTime;

        float m_lastCountDownTime;
        float m_countDownTime;
        float m_countDownTimeRemain;
};

#endif // TIMER_H
