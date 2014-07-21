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
    struct AnimationSetting
    {
        std::vector<sf::Vector2f> sequence;//set of texture tiles to loop through
        bool runOnce;//should we run the sequence once, or loop
        float frameDelay;//delay between each frame
    };
    ///temporary
    ///what we need is std::vector<AnimationSetting> m_animationSettings;//where AnimationSetting contains the data of sequence, delay, runOnce,
    std::vector<sf::Vector2f> m_default;
    std::vector<sf::Vector2f> m_damaged;
    std::vector<sf::Vector2f> m_activated;
    std::vector<sf::Vector2f> m_destroyed;

    AnimationLooper m_animLoop;
};

#endif // ANIMATIONCONTROLLER_H
