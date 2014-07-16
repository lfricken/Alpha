#ifndef VARIABLE_H
#define VARIABLE_H

#include "stdafx.h"

enum class Event
{
    /**GENERIC**/
    State,
    Count,
    Triggered,
    Enabled,
    /**GENERIC**/

    /**UNIVERSE**/
    Health = 0,
    Energy,
    /**UNIVERSE**/

    /**GUI**/
    MouseLeft,
    MouseEntered,
    LeftMouseClicked,
    TextChanged,
    ReturnKeyPressed,
    /**GUI**/

    /**GRAPHICS**/
    Texture,///this may not work, what is this for anyway???
    TexCoords,
    /**GRAPHICS**/

    /**AreaTriggers**/
    OnLeft,
};

/**ATTRIBUTE**/
template <typename T>
class Variable
{
public:
    Variable(Event eve, T val) : m_value(val), m_maxValue(val), m_eventName(eve) {}

    Event getEventType() const {return m_eventName;}
    T getValue() const {return m_value;}
    float getValuePercent() const {return  (static_cast<float>(m_value)/static_cast<float>(m_maxValue)) *100;}
    void setValue(T val) {m_value = val;}

    T getMaxValue() const {return m_maxValue;}
    void setMaxValue(T maxVal) {m_maxValue = maxVal;}
protected:
    T m_value;
    T m_maxValue;
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
    HealthData() : Variable(Event::Health, 100), m_armor(0) {}

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
    void heal(T_Health h)
    {
        m_value += h;
        if(m_value > m_maxValue)
            m_value = m_maxValue;
    }
    T_Armor getArmor() const {return m_armor;}
    void setArmor(T_Armor a) {m_armor = a;}
protected:
    T_Armor m_armor;
};


#endif // VARIABLE_H
