#ifndef VALUECHANGER_H
#define VALUECHANGER_H

#include "VariableNames.hpp"

template <class T>
class ValueChanger
{
public:
    ValueChanger(T rate)
    {
        m_timer.getTimeElapsed();
        m_productionRate = rate;
    }
    void produce(Variable<T>& rPool)
    {
        rPool.changeValue(m_timer.getTimeElapsed()*m_productionRate);
    }
protected:
private:
    Timer m_timer;//how much we contribute
    float m_productionRate;
};

#endif // VALUECHANGER_H
