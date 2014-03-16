#ifndef VARIABLE_H
#define VARIABLE_H

#include "stdafx.h"

enum Variable
{
    HEALTH = 0,
    COUNT,
    TEXTURE,
    TEXCOORDS,
};

/**ATTRIBUTE**/
class Attribute
{
public:
    Attribute(Variable a) : varName(a) {}
    Variable varName;
};

/**VAR ATTRIBUTE**/
class Int_Attribute : public Attribute
{
public:
    Int_Attribute(Variable a, int b) : Attribute(a), value(b) {}
    int value;
};
class Float_Attribute : public Attribute
{
public:
    Float_Attribute(Variable a, float b) : Attribute(a), value(b) {}
    float value;
};

/**SPECIFIC ATTRIBUTE**/
class HealthData : public Int_Attribute
{
public:
    HealthData() : Int_Attribute(HEALTH, 100), armor(0) {}
    int takeDamage(int d)
    {
        if(d <= armor)
            return value;
        else
            value -= abs(d-armor);
        return value;
    }
    int armor;
};

#endif // VARIABLE_H
