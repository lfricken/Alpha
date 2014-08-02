#include "ReactorComponent.hpp"

ReactorComponent::ReactorComponent(T_Energy rate)
{
    m_productionRate = rate;
    m_timer.getTimeElapsed();//to set initial time
}
ReactorComponent::~ReactorComponent()
{

}
void ReactorComponent::produce(EnergyPool& rPool)
{
    T_Energy e = m_timer.getTimeElapsed()*m_productionRate;
    ///std::cout << "\n\nEnergyProduction: " << e;

    rPool.give(e);
}
