#include "ForceFieldCore.hpp"
#include "globals.hpp"

ForceFieldCore::ForceFieldCore(const ForceFieldCoreData& rData) : GModule(rData), m_fieldDecor(rData.m_fieldDecorDat)
{
    m_pForceField = rData.pForceField;
    m_energyConsumption = rData.energyConsumption;
    m_cooldown.setCountDown(rData.cooldown);
}
ForceFieldCore::~ForceFieldCore()
{

}
void ForceFieldCore::destruct()
{
    m_pForceField->disable();
    GModule::destruct();
}
void ForceFieldCore::special_1()
{
    if(m_cooldown.isTimeUp())//cooldown to make sure we can't just flick it on and off super fast
    {
        if(m_isEnabled)
            disable();
        else
            enable();
        m_cooldown.restartCountDown();
    }
}
void ForceFieldCore::enablePostHook()
{
    m_pForceField->enable();
    m_fieldDecor.setColor(sf::Color(255,255,255,255));
    std::cout << "\nEnable.";
    GModule::enablePostHook();
    ///should have animation change
}
void ForceFieldCore::disablePostHook()
{
    m_pForceField->disable();
    m_fieldDecor.setColor(sf::Color(0,0,0,0));
        std::cout << "\nDisable.";
    GModule::disablePostHook();
    ///should have animation change
}
void ForceFieldCore::animatePreHook()
{

    m_fieldDecor.setPosition(getCenter());
    m_fieldDecor.setRotation(m_pBody->GetAngle());
    m_fieldDecor.setVelocity(m_pBody->GetLinearVelocity());

    GModule::animatePreHook();
}
bool ForceFieldCore::physUpdate()
{
    if(m_isEnabled)
        if(m_pChunk->getEnergyPool().canConsume(m_energyConsumption*game.getGameUniverse().getPhysTimeStep()))
            m_pChunk->getEnergyPool().changeValue(-m_energyConsumption*game.getGameUniverse().getPhysTimeStep());
        else
            disable();
}










