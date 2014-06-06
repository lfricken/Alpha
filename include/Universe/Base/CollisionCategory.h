#ifndef COLLISIONCATEGORY_H
#define COLLISIONCATEGORY_H

enum class Category///look at classtype.h
{
    None = 0x0000,//we don't collide with anything
    Projectile = 0x0001,
    ShipModule = 0x0002,
    ShipForceField = 0x0004,//wait, if we don't have this, we wont collide with sensors??? that could be a problem
    ShipHullSensor = 0x0008,
    ShipHull = 0x0010,
    Actor = 0x0020,
    Item = 0x0040,

    All = 0xFFFF,
};
constexpr inline int operator |(Category a, Category b)
{
    return static_cast<int>(static_cast<int>(a) | static_cast<int>(b));
}
constexpr inline int operator &(Category a, Category b)
{
    return static_cast<int>(static_cast<int>(a) & static_cast<int>(b));
}

/**what things should collide with**/
enum class MaskBits
{
    None = Category::None,
    EnabledProjectile = Category::ShipModule | Category::ShipForceField,
    DisabledProjectile = Category::ShipHullSensor,

    ShipModule = Category::Projectile,
    ShipForceField = Category::ShipForceField | Category::Projectile,

    ShipHull = Category::ShipHull,
    ShipHullSensor = Category::Projectile,




    All = 0xFFFF,
};
#endif // COLLISIONCATEGORY_H
