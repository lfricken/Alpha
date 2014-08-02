#ifndef EVENTNAMES_H
#define EVENTNAMES_H

enum class Event
{
    /**GENERIC**/
    State,
    Count,
    Triggered,
    Enabled,
    /**GENERIC**/

    /**UNIVERSE**/
    Health = 0,
    Energy,
    Zoom,
    Ammo,
    /**UNIVERSE**/

    /**GUI**/
    MouseLeft,
    MouseEntered,
    LeftMouseClicked,
    TextChanged,
    ReturnKeyPressed,
    /**GUI**/

    /**GRAPHICS**/
    Texture,///this may not work, what is this for anyway???
    TexCoords,
    /**GRAPHICS**/

    /**AreaTriggers**/
    OnLeft,
};

#endif // EVENTNAMES_H
