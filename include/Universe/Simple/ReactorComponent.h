#ifndef REACTORCOMPONENT_H
#define REACTORCOMPONENT_H

#include "VariableNames.h"
#include "Timer.h"

class ReactorComponent
{
    public:
        ReactorComponent(T_Energy rate);
        virtual ~ReactorComponent();

        void produce(EnergyPool& rPool);

    protected:
    private:
        Timer m_timer;
        T_Energy m_productionRate;
};

#endif // REACTORCOMPONENT_H
