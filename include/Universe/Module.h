#ifndef DMODULE_H
#define DMODULE_H

#include <MultipleInheritance/IOBase.h>
#include <MultipleInheritance/PhysicsBase.h>

struct ModuleData
{
    std::string type;
    PhysicsBaseData physicsData;
};


class Module : public IOBase, public PhysicsBase
{
    public:
        Module(ModuleData& data);
        virtual ~Module();

    protected:
    private:
};

#endif // DMODULE_H
