#ifndef ANGLE_H
#define ANGLE_H

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

#endif // ANGLE_H
