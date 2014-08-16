#include "AmmoStorage.hpp"
#include "globals.hpp"

AmmoStorage::AmmoStorage(const AmmoStorageData& rData) : GModule(static_cast<GModuleData>(rData)), m_capacity(rData.capacity)
{
    m_ammoType = rData.ammoType;
    m_spAmmoGroup = rData.pChunk->getAmmoGroupSPtr();
    m_pAmmoFill = dynamic_cast<TriangleFan*>(game.getGameUniverse().getGfxCompFactory().generate(rData.fillData));

    if(m_isEnabled)
        enable();
    else
        disable();
    m_spAmmoGroup->getAmmo(m_ammoType).changeValue(rData.comesWith);
}
AmmoStorage::~AmmoStorage()
{
    m_capacity.take(m_spAmmoGroup->getAmmo(m_ammoType));
    m_pAmmoFill->free();
}
void AmmoStorage::enablePostHook()
{
    m_capacity.give(m_spAmmoGroup->getAmmo(m_ammoType));
    GModule::enablePostHook();
}
void AmmoStorage::disablePostHook()
{
    m_capacity.take(m_spAmmoGroup->getAmmo(m_ammoType));
    GModule::disablePostHook();
}
void AmmoStorage::animatePreHook()
{
    m_pAmmoFill->setTextureRotation(m_spAmmoGroup->getAmmo(m_ammoType).getValuePercent()*2*pi*0.01);

    m_pAmmoFill->setPosition(getCenter());
    m_pAmmoFill->setRotation(m_pBody->GetAngle());
    m_pAmmoFill->setVelocity(m_pBody->GetLinearVelocity());
    GModule::animatePreHook();
}
