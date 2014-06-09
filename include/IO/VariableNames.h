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
typedef int T_Health;
typedef int T_Damage;
class HealthData : public Variable<T_Health>
{
public:
    HealthData() : Variable(Health, 100), m_armor(0) {}

    T_Health takeDamage(T_Damage d)
    {
        if(d <= m_armor)
            return m_value;
        else
            m_value -= d-m_armor;
        return m_value;
    }
    void heal(T_Health h)    {m_value += h;}
    T_Health getArmor() const    {return m_armor;}
    void setArmor(T_Health a)    {m_armor = a;}
protected:
    T_Health m_armor;
};


#endif // VARIABLE_H
