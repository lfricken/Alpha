#include "Radar.hpp"

Radar::Radar(const RadarData& rData) : GModule(static_cast<GModuleData>(rData)), m_zoomComponent(rData.zoomAdd), m_dish(rData.dishData)
{
    m_spZoomPool = rData.pChunk->getZoomPoolSPtr();
    m_dish.setEnabled(true);

    if(m_isEnabled)
        enable();
    else
        disable();
}
Radar::~Radar()
{
    m_zoomComponent.take(*m_spZoomPool);
}
void Radar::enablePostHook()
{
    std::cout <<"\nGiven.";
    m_zoomComponent.give(*m_spZoomPool);
    m_dish.setEnabled(true);
    GModule::enablePostHook();
}
void Radar::disablePostHook()
{
    m_zoomComponent.take(*m_spZoomPool);
    m_dish.setEnabled(false);
    GModule::disablePostHook();
}
void Radar::animatePreHook()
{
    m_dish.update(getCenter(), m_pBody->GetAngle(), m_pBody->GetLinearVelocity());
    GModule::animatePreHook();
}
