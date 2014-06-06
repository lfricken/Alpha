#ifndef VARIABLE_H
#define VARIABLE_H

#include "stdafx.h"

enum Event
{
    /**GENERIC**/
    State,
    Count,
    /**GENERIC**/

    /**UNIVERSE**/
    Health = 0,
    Energy,
    /**UNIVERSE**/

    /**GUI**/
    MouseLeft,
    MouseEntered,
    LeftMouseClicked,
    /**GUI**/

    /**GRAPHICS**/
    Texture,///this may not work, what is this for anyway???
    TexCoords,
    /**GRAPHICS**/
};

/**ATTRIBUTE**/
template <typename T>
class Variable
{
public:
    Variable(Event eve, T val) : m_value(val), m_eventName(eve) {}

    Event getEventType() const  {return m_eventName;}
    T getValue() const  {return m_value;}
    void setValue(T val)    {m_value = val;}
protected:
    T m_value;
private:
    Event m_eventName;
};


/***********************/
/**SPECIFIC ATTRIBUTES**/
/***********************/
#define HealthT int
class HealthData : public Variable<HealthT>
{
public:
    HealthData() : Variable(Health, 100), m_armor(0) {}

    HealthT takeDamage(HealthT d)
    {
        if(d <= m_armor)
            return m_value;
        else
            m_value -= d-m_armor;
        return m_value;
    }
    void heal(HealthT h)    {m_value += h;}
    HealthT getArmor() const    {return m_armor;}
    void setArmor(HealthT a)    {m_armor = a;}
protected:
    HealthT m_armor;
};
#undef HealthT

#endif // VARIABLE_H
