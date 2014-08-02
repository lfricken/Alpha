#include "Capacitor.hpp"

Capacitor::Capacitor(const CapacitorData& rData) : GModule(static_cast<GModuleData>(rData)), m_capacity(rData.energyStorage)
{
    if(m_isEnabled)
        enable();
    else
        disable();
}
Capacitor::~Capacitor()
{
    m_capacity.take(m_pChunk->getEnergyPool());
}
void Capacitor::enable()
{
    //std::cout << "\nDerived.";
    m_capacity.give(m_pChunk->getEnergyPool());
    GModule::enable();
}
void Capacitor::disable()
{
    //std::cout << "\nDerived2222.";
    m_capacity.take(m_pChunk->getEnergyPool());
    GModule::disable();
}
