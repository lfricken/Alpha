#ifndef TRIGGER_H
#define TRIGGER_H

#include "Module.h"

struct TriggerData : public ModuleData
{
    TriggerData() :
        ModuleData()
    {
        isSensor = true;
        butes.setBute(isSolid, false);
        butes.setBute(isDestructable, false);
    }
};

class Trigger : public Module
{
public:
    Trigger();
    Trigger(const TriggerData& rData);
    virtual ~Trigger();

    virtual int startContact(PhysicsBase* pOther);
    virtual int endContact(PhysicsBase* pOther);

    /**IO-SYSTEM**/
    virtual IOBaseReturn input(IOBaseArgs);

    virtual void trigger();
    virtual void sendFriends(const std::string& targetName);//send a list of IDs that we have
protected:
private:
    virtual void f_initialize(const TriggerData& rData);

    std::vector<unsigned int> m_targetIDs;
};

#endif // TRIGGER_H
