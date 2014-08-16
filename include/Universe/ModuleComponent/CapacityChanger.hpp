#ifndef CAPACITYCHANGER_H
#define CAPACITYCHANGER_H

#include "VariableNames.hpp"

template <class T>
class CapacityChanger
{
public:
    CapacityChanger(T contribution)
    {
        hasContributed = false;
        m_addition = contribution;
    }
    void give(Variable<T>& rPool)
    {
        if(not hasContributed)
        {
            hasContributed = true;
            rPool.changeMax(m_addition);
        }
    }
    void take(Variable<T>& rPool)
    {
        if(hasContributed)
        {
            hasContributed = false;
            rPool.changeMax(-m_addition);
        }
    }
protected:
private:
    bool hasContributed;
    T m_addition;//how much we contribute
};

#endif // CAPACITYCHANGER_H
