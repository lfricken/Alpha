#ifndef DMODULE_H
#define DMODULE_H

#include <MultipleInheritance/IOBase.h>
#include <MultipleInheritance/PhysicsBase.h>

struct ModuleData : public Data
{
    PhysicsBaseData physicsData;
};


class Module : public PhysicsBase
{
    public:
        Module(ModuleData& data);
        virtual ~Module();

    protected:
    private:
};

#endif // DMODULE_H
