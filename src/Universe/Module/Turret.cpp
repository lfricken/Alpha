#include "Turret.hpp"
#include "Intelligence.hpp"

Turret::Turret(const TurretData& rData) : GModule(static_cast<GModuleData>(rData)), m_linker(this)
{
    f_initialize(rData);
}
Turret::~Turret()
{

}
void Turret::f_initialize(const TurretData& rData)
{
    m_linker.link(&m_pChunk->add(rData.weaponData)->getLinker());
    m_firesPrimary = rData.firesPrimary;
    m_firesSecondary = rData.firesSecondary;
}
void Turret::primary(const b2Vec2& coords)
{
    if(!isDestroyed() and m_firesPrimary and m_linker.isLinked())
        m_linker.getTargetPtr()->primary(coords);
}
void Turret::secondary(const b2Vec2& coords)
{
    if(not isDestroyed() and m_firesSecondary and m_linker.isLinked())
        m_linker.getTargetPtr()->secondary(coords);
}
void Turret::aim(const b2Vec2& coords)
{
    if((!isDestroyed()) and m_linker.isLinked())
        m_linker.getTargetPtr()->aim(getCenter(), coords);
}
bool Turret::physUpdate()
{
    if(m_pChunk->getLinker().isLinked())
        m_linker.getTargetPtr()->aim(getCenter(), m_pChunk->getLinker().getTargetPtr()->getAim());

    if((not isDestroyed()) and m_linker.isLinked())
        m_linker.getTargetPtr()->checkFireState(getCenter());
    return true;
}
Link<Turret, Weapon>& Turret::getLinker()
{
    return m_linker;
}
