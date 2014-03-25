#ifndef CLASSTYPE_H
#define CLASSTYPE_H

#include "stdafx.h"

enum ClassType///look at COLLISIONCATEGORY.h, and classes.txt
{
    UNKNOWN = 0,
    ROOTGAME,

    MODULE,
    TRIGGER,

    GMODULE,
    ARMOR,

    CHUNK,
    SHIP,
    CREATURE,

    PLAYER,
    SI,
};

#endif // CLASSTYPE_H
