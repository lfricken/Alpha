#ifndef ROTATE_H
#define ROTATE_H

#include "stdafx.h"
#include "Angles.h"

/**
coords are coordinates in an array (take as a pointer to the original)
size is the total size of the vector, so 1 element in the array means you pass in 1
angle is how much you rotate it in radians
**/
template<class T>
inline void RotateCoordinatesRads(T coords[], unsigned int size, float angle, T rotationPoint)///rotates about origin
{
    T backup;
    for(unsigned int i = 0; i<size; ++i)/**center the coordinates on 0,0**/
    {
        coords[i] -= rotationPoint;
    }
    for(unsigned int i = 0; i<size; ++i)/**rotate them**/
    {
        backup = coords[i];
        coords[i].x = cos(-angle)*backup.x + sin(-angle)*backup.y;
        coords[i].y = -sin(-angle)*backup.x + cos(-angle)*backup.y;
    }
    for(unsigned int i = 0; i<size; ++i)/**move the coordinates back out**/
    {
        coords[i] += rotationPoint;
    }
}
/**
coords are coordinates in an array (take as a pointer to the original)
size is the total size of the vector, so 1 element in the array means you pass in 1
angle is how much you rotate it in degrees
**/

template<class T>
inline void RotateCoordinatesDegs(T coords[], unsigned int size, float angle, T rotationPoint)///rotates about origin
{
    T backup;
    for(unsigned int i = 0; i<size; ++i)/**center the coordinates on 0,0**/
    {
        coords[i] -= rotationPoint;
    }
    for(unsigned int i = 0; i<size; ++i)/**rotate them**/
    {
        backup = coords[i];
        coords[i].x = cos(degToRad(-angle))*backup.x + sin(degToRad(-angle))*backup.y;
        coords[i].y = -sin(degToRad(-angle))*backup.x + cos(degToRad(-angle))*backup.y;
    }
    for(unsigned int i = 0; i<size; ++i)/**move the coordinates back out**/
    {
        coords[i] += rotationPoint;
    }
}
template<class T>
inline T FindCenter(const T coords[], unsigned int size)///rotates about origin
{
    if(size < 1)
        return T(0, 0);

    T topLeft = coords[0];
    T bottomRight = coords[0];
    T center = coords[0];
    unsigned int i = 0;

    for(i = 0; i < size; ++i)/**find top**/
        if(coords[i].y < topLeft.y)
            topLeft.y = coords[i].y;

    for(i = 0; i < size; ++i)/**find left**/
        if(coords[i].x < topLeft.x)
            topLeft.x = coords[i].x;

    for(i = 0; i < size; ++i)/**find bottom**/
        if(coords[i].y > bottomRight.y)
            bottomRight.y = coords[i].y;

    for(i = 0; i < size; ++i)/**find right**/
        if(coords[i].x > bottomRight.x)
            bottomRight.x = coords[i].x;

    /**compute center from topLeft and bottomRight**/
    center.x = (topLeft.x + bottomRight.x)/2;
    center.y = (topLeft.y + bottomRight.y)/2;
    return center;
}
#endif //ROTATE_H
