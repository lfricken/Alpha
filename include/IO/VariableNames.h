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
typedef T_Health T_Armor;
typedef std::tuple<T_Health, T_Armor> T_Damage;
enum DamageMod
{
    Generic = 0,
    Pierce,
};

class HealthData : public Variable<T_Health>
{
public:
    HealthData() : Variable(Health, 100), m_armor(0) {}

    T_Health takeDamage(T_Damage d)
    {
        T_Armor armor = m_armor;
        armor -= std::get<Pierce>(d);
        if(armor < 0)
            armor = 0;

        if(std::get<Generic>(d) <= armor)
            return m_value;
        else
            m_value -= std::get<Generic>(d)-armor;
        return m_value;
    }
    void heal(T_Health h)    {m_value += h;}
    T_Armor getArmor() const    {return m_armor;}
    void setArmor(T_Armor a)    {m_armor = a;}
protected:
    T_Armor m_armor;
};


#endif // VARIABLE_H
