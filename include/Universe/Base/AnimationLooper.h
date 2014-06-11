#ifndef ANIMATIONLOOPER_H
#define ANIMATIONLOOPER_H

#include "stdafx.h"
#include "Timer.h"

class AnimationLooper
{
    public:
        AnimationLooper();
        virtual ~AnimationLooper();

        void restart();//starts from beginning
        bool start();//starts the animation loop, returns true if it was in stop mode
        bool stop();//stops the animation loop, returns true if it wasn't already stopped

        void setDelay(float delay);//delay to set the timer
        void setSequence(const std::vector<sf::Vector2f>& sequence);//sequence of tiles to loop through
        const sf::Vector2f& getTile();//get the current tile we should be on

    protected:
    private:
        Timer m_timer;//helps control time delay between each animation frame

        float m_lastSwitchTime;//stores the last time we changed our texture tile
        float m_accumulatedTime;//stores residual time left over from a switch, like 0.01 seconds.
        bool m_stopped;

        std::vector<sf::Vector2f> m_sequence;//a sequence of tile coordinates to loop through
        std::vector<sf::Vector2f>::const_iterator m_it;//our current position in the sequence, it is what we should display when we are asked for something
};

#endif // ANIMATIONLOOPER_H
