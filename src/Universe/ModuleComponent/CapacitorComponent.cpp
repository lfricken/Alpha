#include "CapacitorComponent.hpp"

CapacitorComponent::CapacitorComponent(T_Energy contribution)
{
    m_maxEnergyAddition = contribution;
    hasContributed = false;
}
CapacitorComponent::~CapacitorComponent()
{

}
void CapacitorComponent::give(EnergyPool& rPool)
{
    if(hasContributed == false)
    {
        hasContributed = true;
        rPool.changeMax(m_maxEnergyAddition);
    }
}
void CapacitorComponent::take(EnergyPool& rPool)
{
    if(hasContributed == true)
    {
        hasContributed = false;
        rPool.changeMax(-m_maxEnergyAddition);
    }
}
