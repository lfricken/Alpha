
#ifndef VARIABLE_H
#define VARIABLE_H

enum Variable
{
    CHANGE = 0,
    HEALTH,
    TEXTURE,
    TEXCOORDS,
};
struct Int_Attribute
{
    Int_Attribute(Variable a, int b) : varName(a), value(b) {}
    Variable varName;
    int value;
};


struct HealthData : public Int_Attribute
{
    HealthData() : Int_Attribute(HEALTH, 100), armor(0) {}
    int armor;
};

#endif // VARIABLE_H
