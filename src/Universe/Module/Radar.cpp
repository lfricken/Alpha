#include "Radar.hpp"

Radar::Radar(const RadarData& rData, std::tr1::shared_ptr<ZoomPool> spZPool) : GModule(static_cast<GModuleData>(rData)), m_zoomComponent(rData.zoomMult), m_dish(rData.dishData)
{
    m_spZoomPool = spZPool;
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
