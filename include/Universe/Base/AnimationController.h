#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include "stdafx.h"

#include "AnimationLooper.h"
#include "AnimationState.h"



/**used by GraphicsBase to control animation state**/
//has a state, which controls what sequence animLoop should be using
//and has an offset to control where on the texture the looping is happening (as opposed to just 0,0 origin)
class AnimationController
{
    public:
        AnimationController();
        virtual ~AnimationController();

        void load(const std::string& animationFile);//these are used to control what the various animation states should do
        const sf::Vector2f& getTile();

        void setState(AnimationState stat);

    protected:
    private:
    ///temporary
    std::vector<sf::Vector2f> m_default;
    std::vector<sf::Vector2f> m_damaged;
    std::vector<sf::Vector2f> m_destroyed;

    AnimationLooper m_animLoop;
};

#endif // ANIMATIONCONTROLLER_H
