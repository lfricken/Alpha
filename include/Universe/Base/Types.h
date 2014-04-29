#ifndef CLASSTYPE_H
#define CLASSTYPE_H

#include "stdafx.h"

enum ClassType///look at physbase.h
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
