#ifndef ROTATE_H
#define ROTATE_H

#include "stdafx.h"

/**
coords are coordinates in an array (take as a pointer to the original)
size is the total size of the vector, so 1 element in the array means you pass in 1
angle is how much you rotate it in radians
**/
template<class T>
inline void RotateCoordinatesRads(T coords[], unsigned int size, float angle)///rotates about origin
{
    T backup = coords;
    for(int i = 0; i<size; ++i)
    {
        coords.x = cos(angle)*backup.x + sin(angle)*backup.y;
        coords.y = -sin(angle)*backup.x + cos(angle)*backup.y;
    }
}
/**
coords are coordinates in an array (take as a pointer to the original)
size is the total size of the vector, so 1 element in the array means you pass in 1
angle is how much you rotate it in degrees
**/

template<class T>
inline void RotateCoordinatesDegs(T coords[], unsigned int size, float angle)///rotates about origin
{
    T backup = coords;
    for(int i = 0; i<size; ++i)
    {
        coords.x = cos(180.0*angle/PI)*backup.x + sin(180.0*angle/PI)*backup.y;
        coords.y = -sin(180.0*angle/PI)*backup.x + cos(180.0*angle/PI)*backup.y;
    }
}
#endif //ROTATE_H
