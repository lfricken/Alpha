#ifndef ROTATE_H
#define ROTATE_H

#include "stdafx.h"
#include "Angles.h"


/**
coords are coordinates in an array (take as a pointer to the original)
size is the total size of the vector, so 1 element in the array means you pass in 1
angle is how much you rotate it in degrees
**/
template<class T>
inline void RotateCoordinatesDegs(std::vector<T>& coords, float angle, T rotationPoint)///rotates about origin
{
    unsigned int size = coords.size();
    T backup;
    for(unsigned int i = 0; i<size; ++i)/**center the coordinates on 0,0**/
    {
        coords[i] -= rotationPoint;
    }
    for(unsigned int i = 0; i<size; ++i)/**rotate them**/
    {
        backup = coords[i];
        coords[i].x = cos(leon::degToRad(-angle))*backup.x + sin(leon::degToRad(-angle))*backup.y;
        coords[i].y = -sin(leon::degToRad(-angle))*backup.x + cos(leon::degToRad(-angle))*backup.y;
    }
    for(unsigned int i = 0; i<size; ++i)/**move the coordinates back out**/
    {
        coords[i] += rotationPoint;
    }
}
template<class T>
inline void RotateCoordinatesDegs(T coords[], unsigned int size, float angle, T rotationPoint)///rotates about origin
{
    std::vector<T> vec;
    for(unsigned int i=0; i<size; ++i)
        vec.push_back(coords[i]);

    RotateCoordinatesDegs(vec, angle, rotationPoint);//call better function

    for(unsigned int i=0; i<size; ++i)
        coords[i] = vec[i];
}
template<class T>
inline void RotateCoordinatesRads(T coords[], unsigned int size, float angle, T rotationPoint)///rotates about origin
{
    RotateCoordinatesDegs(coords, size, leon::radToDeg(angle), rotationPoint);
}


/**
Find Center of coords, simply by constructing an AABB(Bounding Box), and getting it's center coordinate
**/
template<class T>
inline T FindCenter(const std::vector<T>& coords)/**we want to rotate about center because otherwise, strange things will happen**/
{
    unsigned int size = coords.size();
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
template<class T>
inline T FindCenter(const T coords[], unsigned int size)/**we want to rotate about center because otherwise, strange things will happen**/
{
    std::vector<T> vec;
    for(unsigned int i=0; i<size; ++i)
        vec.push_back(coords[i]);

    return FindCenter(vec);
}
#endif //ROTATE_H
