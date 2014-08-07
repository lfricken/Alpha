#ifndef CLASSTYPE_H
#define CLASSTYPE_H

#include "stdafx.hpp"

enum ClassType///we should revise this possible
{
    /**default**/
    UNKNOWN = 0,

    /**UNIVERSE, GAME, GUI, DESTINATION ect.**/
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

    /**Decoration**/
    DECORATION,

    /**MODULES**/
    MODULE,//basic module type
    HULL,//for ship-ship collision, and for telling our projectiles when they have left the firing ship
    TRIGGER,//standard trigger
    FORCE,//force field

    /**GMODULES**/
    GMODULE,//basic gModule type
    ARMOR,
    CAPACITOR,
    REACTOR,
    FLOOR,
    THRUSTER,
    TURRET,
    STORAGE,
    SENSOR,


    /**CHUNKS**/
    CHUNK,//basic chunk type
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
