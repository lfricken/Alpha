#ifndef DMODULE_H
#define DMODULE_H

#include <IOBase.h>
#include <PhysicsBase.h>

struct ModuleData : public PhysicsBaseData
{
    ModuleData() :
        PhysicsBaseData()
    {
        type = ClassType::MODULE;
        categoryBits = Category::ShipModule;
        maskBits = Mask::ShipModuleNorm;
        butes.setBute(isSolid, true);
        butes.setBute(isDestructable, false);
    }
};


class Module : public PhysicsBase
{
public:
    Module();
    Module(const ModuleData& data);
    virtual ~Module();

protected:
private:
    virtual void f_initialize(const ModuleData& data);
};

#endif // DMODULE_H
