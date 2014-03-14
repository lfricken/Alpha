#ifndef COURIER_H
#define COURIER_H

#include "Condition.h"
#include "Package.h"

struct Courier//just used to couple a Condition to its Package
{
    Condition condition;
    Package package;
};

#endif // COURIER_H
