#ifndef ANGLE_H
#define ANGLE_H

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

}

#endif // ANGLE_H
