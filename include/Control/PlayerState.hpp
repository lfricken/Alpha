#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

enum class PlayerState//used to determine how player commands should be interpreted from keyboard
{
    Playing = 0,
    Interfacing,
    Editing,
};

#endif // PLAYERSTATE_H
