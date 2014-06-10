#include "GModule.h"
#include "globals.h"
#include "PacketMod.hpp"

GModule::GModule():
    PhysicsBase(),
    GraphicsBase()
{
    GModuleData data;
    f_initialize(data);
}
GModule::GModule(const GModuleData& data) :
    PhysicsBase(static_cast<PhysicsBaseData>(data)),
    GraphicsBase(static_cast<GraphicsBaseData>(data), data.halfSize, data.offset, data.rotation)
{
    f_initialize(data);
}
GModule::~GModule()
{

}
void GModule::f_initialize(const GModuleData& data)
{
    m_health.setArmor(data.armor);
    m_health.setValue(data.health);

    m_isDestroyed = false;
}
IOBaseReturn GModule::input_1(IOBaseArgs)
{
    T_Damage amount;
    if(rInput >> amount)//successful
    {
        std::cout << "\nHealth Remaining: [" << damage(amount) << "].";
    }
    else
    {
        ///ERROR LOG
        std::cout << "\nError, packet had [";
        std::cout << std::get<DamageMod::Generic>(amount) << "].";
    }
}
T_Health GModule::damage(T_Damage damage)
{
    m_health.takeDamage(damage);
    f_varEvent(m_health.getValue(), m_health.getEventType());

    if(m_health.getValue() <= 0)//if our health drops too low
        destruct();

    return m_health.getValue();
}
T_Health GModule::heal(T_Health h)
{
    m_health.heal(h);
    f_varEvent(m_health.getValue(), m_health.getEventType());
    return m_health.getValue();
}
T_Health GModule::getHealth() const
{
    return m_health.getValue();
}
void GModule::destruct()
{
    if(m_attributes.getBute(Butes::isDestructable)) ///DO DESTRUCTION STUFF HERE
    {
        ///SOMETHING COOL FOR NOW
        b2Filter filter = m_pFixture->GetFilterData();
        filter.maskBits = static_cast<uint16>(MaskBits::ShipModuleBroke);
        m_pFixture->SetFilterData(filter);

        m_isDestroyed = true;
        setTexTile(sf::Vector2f(4, 0));
    }
}
