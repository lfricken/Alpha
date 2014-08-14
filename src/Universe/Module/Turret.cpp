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
    if((not isDestroyed()) and m_firesPrimary and m_linker.isLinked())
        m_linker.getTargetPtr()->primary(coords);
}
void Turret::secondary(const b2Vec2& coords)
{
    if((not isDestroyed()) and m_firesSecondary and m_linker.isLinked())
        m_linker.getTargetPtr()->secondary(coords);
}
void Turret::aim(const b2Vec2& coords)
{
    if((not isDestroyed()) and m_linker.isLinked())
        m_linker.getTargetPtr()->aim(getCenter(), coords);
}
bool Turret::physUpdate()
{
    if(m_linker.isLinked())
    {
        m_linker.getTargetPtr()->updatePosition(getCenter());
        m_linker.getTargetPtr()->updateVelocity(m_pBody->GetLinearVelocity());
        if(not isDestroyed())
            m_linker.getTargetPtr()->checkFireState();
    }

    return true;
}
void Turret::destructHook()
{
   // if(m_linker.isLinked())
    //    m_linker.getTargetPtr()->setPivot(false);
    GModule::destructHook();
}
Link<Turret, Weapon>& Turret::getLinker()
{
    return m_linker;
}
