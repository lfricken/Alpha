#ifndef ANIMATIONLOOPER_H
#define ANIMATIONLOOPER_H

#include "stdafx.h"
#include "Timer.h"

//used by animation controler to
class AnimationLooper
{
    typedef std::vector<sf::Vector2f>::const_iterator const_it;

    public:
        AnimationLooper();
        virtual ~AnimationLooper();

        void runOnce(bool once);

        void restart();//starts from beginning
        void start();//starts the animation loop
        void stop();//stops the animation loop

        void setDelay(float delay);//delay to set the timer
        void setSequence(const std::vector<sf::Vector2f>& sequence);//sequence of tiles to loop through
        const sf::Vector2f& getTile();//get the current tile we should be on

    protected:
    private:
        const_it f_getNext();

        Timer m_timer;//helps control time delay between each animation frame

        float m_delay;
        float m_accumulatedTime;//stores residual time left over from a switch, like 0.01 seconds.
        bool m_stopped;
        bool m_runOnce;

        std::vector<sf::Vector2f> m_sequence;//a sequence of tile coordinates to loop through
        const_it m_it;//our current position in the sequence, it is what we should display when we are asked for something
        const_it m_itLast;//used if we don't need the next one
};

#endif // ANIMATIONLOOPER_H
