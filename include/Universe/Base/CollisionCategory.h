#ifndef COLLISIONCATEGORY_H
#define COLLISIONCATEGORY_H

namespace collide//used to differentiate between other enums and class names
{
enum CollisionCategory///look at classtype.h
{
    None = 0x0000,//we don't collide with anything
    Projectile = 0x0001,
    ShipModule = 0x0002,
    Sensor = 0x0004,
    ShipHull = 0x0008,
    Creature = 0x0010,
    Item = 0x0020,
    All = 0xFFFF,
};
}
#endif // COLLISIONCATEGORY_H
