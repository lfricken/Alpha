#include "Capacitor.hpp"

Capacitor::Capacitor(const CapacitorData& rData, std::tr1::shared_ptr<EnergyPool> spEpool) : GModule(static_cast<GModuleData>(rData)), m_capacity(rData.energyStorage)
{
    m_spEnergyPool = spEpool;

    if(m_isEnabled)
        enable();
    else
        disable();
}
Capacitor::~Capacitor()
{
    m_capacity.take(*m_spEnergyPool);
}
void Capacitor::enablePostHook()
{
    m_capacity.give(*m_spEnergyPool);
    GModule::enablePostHook();
}
void Capacitor::disablePostHook()
{
    m_capacity.take(*m_spEnergyPool);
    GModule::disablePostHook();
}
void Capacitor::animatePreHook()
{
    ///if(m_stateGraph.getState() == State::Nominal)

}
