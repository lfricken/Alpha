#ifndef VARIABLE_H
#define VARIABLE_H

#include "stdafx.h"
#include "EventNames.h"
#include "ActiveEventer.h"

///WE SHOULD PASS A COURIER POINTER AND STORE IT, SO WE CAN DO OUR OWN CHECKS for events
/**ATTRIBUTE**/
template <typename T>
class Variable
{
public:
    Variable(ActiveEventer* pEventer, Event type, T val, T maxVal) : m_value(val), m_maxValue(maxVal), m_pEventer(pEventer), m_eventName(type) {}

    T getValue() const
    {
        return m_value;
    }
    float getValuePercent() const
    {
        return (static_cast<float>(m_value)/static_cast<float>(m_maxValue))*100;
    }
    void setValue(T val)
    {
        m_value = val;
        if(m_value > m_maxValue)
            m_value = m_maxValue;
        f_eventCheck();
    }
    void changeValue(T val)
    {
        m_value += val;
        if(m_value > m_maxValue)
            m_value = m_maxValue;
        f_eventCheck();
    }
    T getMaxValue() const
    {
        return m_maxValue;
    }
    void setMaxValue(T maxVal)
    {
        m_maxValue = maxVal;
    }
protected:
    void f_eventCheck()
    {
        std::ostringstream converted;
        converted << m_value;
        m_pEventer->event(converted.str(), m_eventName);
    }
private:
    T m_value;
    T m_maxValue;
    ActiveEventer* m_pEventer;
    Event m_eventName;
};


/***********************/
/**SPECIFIC ATTRIBUTES**/
/***********************/
typedef int T_Health;
typedef T_Health T_Armor;


typedef std::tuple<T_Health, T_Armor> T_Damage;
enum DamageKey
{
    Generic = 0,
    Pierce,
};

class HealthData : public Variable<T_Health>
{
public:
    HealthData(ActiveEventer* pEventer) : Variable(pEventer, Event::Health, 100, 100), m_armor(0) {}

    T_Health takeDamage(T_Damage d)
    {
        T_Armor armor = m_armor;
        armor -= std::get<Pierce>(d);
        if(armor < 0)
            armor = 0;

        if(std::get<Generic>(d) <= armor)
            return getValue();
        else
            changeValue(-std::get<Generic>(d)+armor);
        return getValue();
    }
    void heal(T_Health h)
    {
        changeValue(h);
    }
    T_Armor getArmor() const
    {
        return m_armor;
    }
    void setArmor(T_Armor a)
    {
        m_armor = a;
    }
protected:
    T_Armor m_armor;
};



typedef float T_Energy;
class EnergyPool : protected Variable<T_Energy>
{
public:
    EnergyPool(ActiveEventer* pEventer) : Variable(pEventer, Event::Energy, 0, 0) {}

    bool consume(T_Energy amount)
    {
        if(amount <= getValue())
        {
            changeValue(-amount);
            return true;
        }
        else
            return false;
    }
    void give(T_Energy amount)
    {
        changeValue(amount);
    }
};


#endif // VARIABLE_H
