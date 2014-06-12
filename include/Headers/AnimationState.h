#ifndef ANIMATIONSTATE_H
#define ANIMATIONSTATE_H

#include "stdafx.h"
#include "Timer.h"

enum AnimationState
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
