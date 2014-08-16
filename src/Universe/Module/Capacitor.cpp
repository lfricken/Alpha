#include "Capacitor.hpp"
#include "globals.hpp"

Capacitor::Capacitor(const CapacitorData& rData, std::tr1::shared_ptr<EnergyPool> spEpool) : GModule(static_cast<GModuleData>(rData)), m_capacity(rData.energyStorage)
{
    m_spEnergyPool = spEpool;
    m_pEnergyFill = dynamic_cast<TriangleFan*>(game.getGameUniverse().getGfxCompFactory().generate(rData.fillData));

    if(m_isEnabled)
        enable();
    else
        disable();

    m_spEnergyPool->changeValue(rData.comesWith);
}
Capacitor::~Capacitor()
{
    m_capacity.take(*m_spEnergyPool);
    m_pEnergyFill->free();
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
    m_pEnergyFill->setTextureRotation(m_spEnergyPool->getValuePercent()*2*pi*0.01);

    m_pEnergyFill->setPosition(getCenter());
    m_pEnergyFill->setRotation(m_pBody->GetAngle());
    m_pEnergyFill->setVelocity(m_pBody->GetLinearVelocity());
    GModule::animatePreHook();
}
