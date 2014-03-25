#ifndef VARIABLE_H
#define VARIABLE_H

#include "stdafx.h"

enum Variable
{
    HEALTH = 0,
    ENERGY,
    STATE,
    COUNT,
    TEXTURE,
    TEXCOORDS,
};

/**ATTRIBUTE**/
class Attribute
{
public:
    Attribute(Variable a) : varName(a) {}
    Variable getVarType() const {return varName;}
private:
    Variable varName;
};

/**VAR_TYPE ATTRIBUTE**/
class Int_Attribute : public Attribute
{
public:
    Int_Attribute(Variable a, int b) : Attribute(a), value(b) {}
    int getValue() const {return value;}
    void setValue(int c) {value = c;}
protected:
    int value;
};
class Float_Attribute : public Attribute
{
public:
    Float_Attribute(Variable a, float b) : Attribute(a), value(b) {}
    float getValue() const {return value;}
    void setValue(float c) {value = c;}
protected:
    float value;
};



/***********************/
/**SPECIFIC ATTRIBUTES**/
/***********************/
class HealthData : public Int_Attribute
{
public:
    HealthData() : Int_Attribute(HEALTH, 100), armor(0) {}
    int takeDamage(int d)
    {
        if(d <= armor)
            return value;
        else
            value -= d-armor;
        return value;
    }
    void heal(int h){value += h;}
protected:
    int armor;
};

#endif // VARIABLE_H
