#ifndef CLASSTYPE_H
#define CLASSTYPE_H

#include "stdafx.h"

enum ClassType///look at COLLISIONCATEGORY.h, and classes.txt
{
    /**default**/
    UNKNOWN = 0,

    /**UNIVERSE, GAME, GUI ect.**/
    //ROOTGAME,///<---whats this for???
    UNIVERSE,
    OVERLAYMANAGER,
    GAME,

    /**GUI**/
    BUTTON,
    PANEL,
    SLIDER,
    CHECKBOX,
    RADIOBUTTON,
    LOADINGBAR,
    EDITBOX,
    MENUBAR,
    TAB,
    LABEL,
    CHILDWINDOW,
    CHATBOX,
    SCROLLBAR,
    LISTBOX,
    COMBOBOX,

    /**MODULES**/
    MODULE,
    TRIGGER,
    FORCE,

    /**GMODULES**/
    GMODULE,
    ARMOR,
    CAPACITOR,
    TURRET,
    FLOOR,

    /**CHUNKS**/
    CHUNK,
    STATION,
    SHIP,
    PROJECTILE,
    ACTOR,
    ITEM,

    /**INTELLIGENCE**/
    PLAYER,
    SI,
};

#endif // CLASSTYPE_H
