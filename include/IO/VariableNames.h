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
    Variable(ActiveEventer* pEventer, Event type, T val, T maxVal, T minVal)
    : m_value(val), m_maxValue(maxVal), m_minValue(minVal), m_pEventer(pEventer), m_eventName(type) {}

    /**GETTERS**/
    T getValue() const
    {
        return m_value;
    }
    float getValuePercent() const
    {
        return (static_cast<float>(m_value-m_minValue)/static_cast<float>(m_maxValue-m_minValue))*100;
    }
    T getMaxValue() const
    {
        return m_maxValue;
    }
    T getMinValue() const
    {
        return m_minValue;
    }
protected:

    /**SETTERS**/
    void setValue(T val)
    {
        m_value = val;

        if(m_value > m_maxValue)
            m_value = m_maxValue;
        else if(m_value < m_minValue)
            m_value = m_minValue;

        f_eventCheck();
    }
    void changeValue(T val)
    {
        m_value += val;

        if(m_value > m_maxValue)
            m_value = m_maxValue;
        else if(m_value < m_minValue)
            m_value = m_minValue;

        f_eventCheck();
    }

    void setMaxValue(T maxVal)
    {
        m_maxValue = maxVal;
        if(m_value > m_maxValue)
            m_value = m_maxValue;
        f_eventCheck();
    }
    void setMinValue(T minVal)
    {
        m_minValue = minVal;
        if(m_value < m_minValue)
            m_value = m_minValue;
        f_eventCheck();
    }
private:
    void f_eventCheck()
    {
        std::ostringstream converted;
        converted << m_value;
        m_pEventer->event(converted.str(), m_eventName);
    }
    T m_value;
    T m_maxValue;
    T m_minValue;

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
    HealthData(ActiveEventer* pEventer, T_Health val, T_Health max) : Variable(pEventer, Event::Health, val, max, 0), m_armor(0) {}

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
class EnergyPool : public Variable<T_Energy>
{
public:
    EnergyPool(ActiveEventer* pEventer, T_Energy val, T_Energy max) : Variable(pEventer, Event::Energy, val, max, 0) {}

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
    void changeMax(T_Energy amount)
    {
        setMaxValue(getMaxValue()+amount);
    }
};


typedef float T_Zoom;
class ZoomPool : public Variable<T_Zoom>
{
public:
    ZoomPool(ActiveEventer* pEventer, T_Zoom val, T_Zoom max, T_Zoom min) : Variable(pEventer, Event::Zoom, val, max, min) {}

    void changeMult(T_Zoom multipleAmount)
    {
        setValue(multipleAmount*getValue());
    }
    void setMaxMaxZoom(T_Zoom maxMax)
    {
        setMaxValue(maxMax);
    }
    void setMinZoom(T_Zoom minZoom)
    {
        setMinValue(minZoom);
    }
    T_Zoom getMinZoom() const
    {
        return getMinValue();
    }
    T_Zoom getMaxZoom() const
    {
        return getValue();
    }
};


#endif // VARIABLE_H
