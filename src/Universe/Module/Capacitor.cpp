#include "Capacitor.hpp"
#include "globals.hpp"

Capacitor::Capacitor(const CapacitorData& rData, std::tr1::shared_ptr<EnergyPool> spEpool) : GModule(static_cast<GModuleData>(rData)), m_capacity(rData.energyStorage)
{
    m_spEnergyPool = spEpool;
    m_energyFill = dynamic_cast<TriangleFan*>(game.getGameUniverse().getGfxCompFactory().generate(rData.fillData));

    if(m_isEnabled)
        enable();
    else
        disable();
}
Capacitor::~Capacitor()
{
    m_capacity.take(*m_spEnergyPool);
    m_energyFill->free();
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
    m_energyFill->setTextureRotation(m_spEnergyPool->getValuePercent()*2*pi*0.01);

    m_energyFill->setPosition(getCenter());
    m_energyFill->setRotation(m_pBody->GetAngle());
    m_energyFill->setVelocity(m_pBody->GetLinearVelocity());
}
