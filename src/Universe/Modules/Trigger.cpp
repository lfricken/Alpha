#include "Trigger.h"

#include "IOManager.h"

Trigger::Trigger() : Module()
{
    TriggerData data;
    f_initialize(data);
}
Trigger::Trigger(const TriggerData& rData) : Module(static_cast<ModuleData>(rData))
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
    m_targetIDs.push_back(pOther->getID());
    trigger();
    return 0;
}
int Trigger::endContact(PhysicsBase* pOther)
{
    for(auto it = m_targetIDs.begin(); it != m_targetIDs.end(); ++it)
        if(*it == pOther->getID())
            m_targetIDs.erase(it);

    return 0;
}
IOBaseReturn Trigger::input(IOBaseArgs)
{
    if(rCommand == "enable")
        enable();
    else if(rCommand == "disable")
        disable();
    else if(rCommand == "trigger")
        trigger();
    else if(rCommand == "sendFriends")
    {
        std::string temp;
        rInput >> temp;
        sendFriends(temp);
    }
    else
    {
        ///ERROR LOG
        std::cout << "\nCommand [" << rCommand << "] was never found.";
    }
}
void Trigger::trigger()
{
    f_varEvent(static_cast<int>(m_targetIDs.size()), Event::Triggered);
}
void Trigger::sendFriends(const std::string& targetName)//send a list of IDs that we have to the arg id
{
    sf::Packet packet;
    /**get id's of our friends**/
    for(auto it = m_targetIDs.begin(); it != m_targetIDs.end(); ++it)
        packet << *it;

    Package pack(targetName, "receiveFriends", packet, 0.0f, Destination::UNIVERSE);
    m_rIOManager.recieve(pack);
}
