#include "Turret.h"


Turret::Turret() : GModule(), m_linker(this)
{
    TurretData data;
    f_initialize(data);
}
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
    if(!isDestroyed() && m_firesPrimary)
        m_linker.getTargetPtr()->primary(coords);
}
void Turret::secondary(const b2Vec2& coords)
{
    if(!isDestroyed() && m_firesSecondary)
        m_linker.getTargetPtr()->secondary(coords);
}
void Turret::aim(const b2Vec2& coords)
{
    if(!isDestroyed())
        m_linker.getTargetPtr()->aim(coords);
}
bool Turret::physUpdate()
{
    m_linker.getTargetPtr()->checkFireState();
    return true;
}
Link<Turret, Weapon>& Turret::getLinker()
{
    return m_linker;
}
