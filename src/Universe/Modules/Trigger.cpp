#include "Trigger.h"

#include "IOManager.h"

Trigger::Trigger() : Module(), m_filter()
{
    TriggerData data;
    f_initialize(data);
}
Trigger::Trigger(const TriggerData& rData) : Module(static_cast<ModuleData>(rData)), m_filter(rData.filterData)
{
    f_initialize(rData);
}
Trigger::~Trigger()
{

}
void Trigger::f_initialize(const TriggerData& rData)
{

}
int Trigger::startContact(PhysicsBase* pOther)
{
    if(passesFilter(pOther))
    {
        m_guests.push_back(pOther);
        objectEntered(pOther);
    }
    return 0;
}
bool Trigger::passesFilter(PhysicsBase* pOther)
{
    return m_filter.passes(pOther->getType(), pOther->getName());
}
void Trigger::objectEntered(PhysicsBase* pOther)
{
    trigger();
}
int Trigger::endContact(PhysicsBase* pOther)
{

    for(auto it = m_guests.begin(); it != m_guests.end(); ++it)
        if(*it == pOther)
        {
            m_guests.erase(it);
            break;
        }

    return 0;
}
IOBaseReturn Trigger::input(IOBaseArgs)
{
    if(rCommand == "trigger")
        trigger();
    else if(rCommand == "sendGuests")
    {
        std::string temp;
        rInput >> temp;
        sendGuests(temp);
    }
    else
        Module::input(rInput, rCommand);
}
void Trigger::trigger()
{
    f_varEvent(static_cast<int>(m_guests.size()), Event::Triggered);
}
void Trigger::sendGuests(const std::string& targetName)//send a list of IDs that we have to the arg id
{
    sf::Packet packet;
    /**get id's of our friends**/
    for(auto it = m_guests.begin(); it != m_guests.end(); ++it)
        packet << *it;

    Package pack(targetName, "receiveFriends", packet, 0.0f, Destination::UNIVERSE, false);
    m_rIOManager.recieve(pack);
}
