#ifndef ANGLE_H
#define ANGLE_H

#include "stdafx.h"
#include "globals.h"

namespace leon
{

template<typename T>
inline float degToRad(T value)
{
    return (pi*value)/180.0;
}
template<typename T>
inline float radToDeg(T value)
{
    return (180.0*value)/pi;
}
template<typename T>
inline float sinL(T value)
{
    ///access global lookup table for sin with the value (we have to create it)
    //return arrayElement!!!;
    return 0;//just until this is created
}
template<typename T>
inline T screenToCart(const T& screenCoords)
{
    return T(screenCoords.x, -screenCoords.y);
}
template<typename T>
inline b2Vec2 sfTob2(const T& screenCoords)
{
    return b2Vec2(screenCoords.x/scale, -screenCoords.y/scale);
}
template<typename T>
inline sf::Vector2<T> b2Tosf(const b2Vec2& worldCoords)
{
    return sf::Vector2<T>(worldCoords.x*scale, -worldCoords.y*scale);
}

}

#endif // ANGLE_H
