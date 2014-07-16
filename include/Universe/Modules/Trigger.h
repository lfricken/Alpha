#ifndef TRIGGER_H
#define TRIGGER_H

#include "Module.h"
#include "Filter.h"

struct TriggerData : public ModuleData
{
    TriggerData() :
        ModuleData(),
        filterData()
    {
        density = 0;
        halfSize = b2Vec2(8,8);
        categoryBits = Category::ShipForceField;
        maskBits = Mask::ShipForceField;
        type = ClassType::TRIGGER;
        isSensor = true;
        butes.setBute(isSolid, false);
        butes.setBute(isDestructable, false);
    }
    FilterData filterData;
};

class Trigger : public Module
{
public:
    Trigger();
    Trigger(const TriggerData& rData);
    virtual ~Trigger();

    int startContact(PhysicsBase* pOther) final;
    int endContact(PhysicsBase* pOther) final;
    bool passesFilter(PhysicsBase* pOther);

    virtual void objectEntered(PhysicsBase* pOther);//passed down the tree

    /**IO-SYSTEM**/
    virtual IOBaseReturn input(IOBaseArgs);

    virtual void trigger();
    void sendGuests(const std::string& targetName);//send a list of IDs that we have

protected:
    std::vector<PhysicsBase*> m_guests;
    Filter m_filter;

private:
    virtual void f_initialize(const TriggerData& rData);
};

#endif // TRIGGER_H
