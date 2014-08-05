#ifndef ANIMATIONSETTING_H
#define ANIMATIONSETTING_H

#include "stdafx.hpp"

typedef std::string AnimationState;
/**
enum class AnimationState
{
    Default = 0,
    Activated,

    Enabled,//animation when enabled is called
    Disabled,

    MoveUp,
    MoveLeft,
    MoveRight,
    MoveDown,

    Damaged,//health < 50%
    Destroyed,//health <= 0%

    Error,
    Null,
};**/


struct AnimationSetting
{
    float delay;//delay between each frame
    AnimationState nextState;
    std::vector<sf::Vector2f> sequence;//set of texture tiles to loop through
};

#endif // ANIMATIONSETTING_H
