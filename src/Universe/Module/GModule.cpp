#include "GModule.hpp"

#include "globals.hpp"
using namespace std;

GModule::GModule():
    PhysicsBase(),
    GraphicsBase(),
    m_health(500, m_pIOComponent->getEventerPtr(), 1000, 1000)
{
    GModuleData data;
    f_initialize(data);
}
GModule::GModule(const GModuleData& data) :
    PhysicsBase(static_cast<PhysicsBaseData>(data)),
    GraphicsBase(static_cast<GraphicsBaseData>(data), data.halfSize, data.offset, data.rotation),
    m_health(data.armor, m_pIOComponent->getEventerPtr(), 1000, 1000)
{
    f_initialize(data);
}
GModule::~GModule()
{

}
void GModule::f_initialize(const GModuleData& data)
{
    m_isDestroyed = false;
}
IOBaseReturn GModule::input(IOBaseArgs)
{
    if(rCommand == "damage")
    {
        T_Damage amount;
        if(rInput >> amount)
            damage(amount);
        else
        {
            std::cout << "\nError in data extraction in input in GModule." << FILELINE;
            ///ERROR LOG
        }
    }
    else if(rCommand == "destruct")
        destruct();
    else
    {
        std::cout << "\nError: [" << rCommand << "] was not recognized as a command." << FILELINE;
        ///ERROR LOG
    }
}
T_Health GModule::damage(T_Damage damage)
{
    m_health.takeDamage(damage);

    if(m_health.getValuePercent() <= 50.0f)
        getAnimationController().setState("Damaged");

    if(m_health.getValue() <= 0)//if our health drops too low
        destruct();

    return m_health.getValue();
}
T_Health GModule::heal(T_Health h)
{
    m_health.heal(h);

    if(isDestroyed() and (m_health.getValuePercent() == 100.0f))//if we reached 100% health
    {
        ///construct();//we have been rebuilt!!!
    }

    return m_health.getValue();
}
T_Health GModule::getHealth() const
{
    return m_health.getValue();
}
void GModule::destruct()
{
    if(m_attributes.getBute(Butes::isDestructable))
    {
        b2Filter filter = m_pFixture->GetFilterData();
        filter.maskBits = static_cast<uint16>(Mask::ShipModuleBroke);
        m_pFixture->SetFilterData(filter);

        m_isDestroyed = true;
        getAnimationController().setState("Destroyed");
        disable();
    }
}
bool GModule::isDestroyed() const
{
    return m_isDestroyed;
}
void GModule::primary(const b2Vec2& coords) {}
void GModule::secondary(const b2Vec2& coords) {}
void GModule::aim(const b2Vec2& coords) {}
void GModule::up() {}
void GModule::down() {}
void GModule::left() {}
void GModule::right() {}
void GModule::rollLeft() {}
void GModule::rollRight() {}
void GModule::special_1() {}
void GModule::special_2() {}
void GModule::special_3() {}
void GModule::special_4() {}
