#include "Capacitor.hpp"
#include "globals.hpp"

Capacitor::Capacitor(const CapacitorData& rData, std::tr1::shared_ptr<EnergyPool> spEpool) : GModule(rData), m_energyFill(rData.fillData), m_capacity(rData.energyStorage)
{
    m_spEnergyPool = spEpool;

    if(m_isEnabled)
        enable();
    else
        disable();

    m_spEnergyPool->changeValue(rData.comesWith);
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
    m_energyFill.setPercentFull(m_spEnergyPool->getValuePercent());

    m_energyFill.setPosition(getCenter());
    m_energyFill.setRotation(m_pBody->GetAngle());
    m_energyFill.setVelocity(m_pBody->GetLinearVelocity());
    GModule::animatePreHook();
}
