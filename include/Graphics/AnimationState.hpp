#ifndef ANIMATIONSTATE_H
#define ANIMATIONSTATE_H

#include "stdafx.hpp"
#include "Timer.hpp"

enum class AnimationState
{
    Default = 0,
    Activated,

    Enabled,
    Disabled,

    MoveUp,
    MoveLeft,
    MoveRight,
    MoveDown,

    Damaged,
    Destroyed,
};

#endif //ANIMATIONSTATE_H
