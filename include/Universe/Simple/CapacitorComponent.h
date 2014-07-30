#ifndef CAPACITORCOMPONENT_H
#define CAPACITORCOMPONENT_H

#include "VariableNames.h"

class CapacitorComponent
{
    public:
        CapacitorComponent(T_Energy contribution);
        virtual ~CapacitorComponent();

        void give(EnergyPool& rPool);
        void take(EnergyPool& rPool);

    protected:
    private:
        bool hasContributed;
        T_Energy m_maxEnergyAddition;
};

#endif // CAPACITORCOMPONENT_H
