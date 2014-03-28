#ifndef DMODULE_H
#define DMODULE_H

#include <IOBase.h>
#include <PhysicsBase.h>

struct ModuleData : public PhysicsBaseData
{
    ModuleData() :
        PhysicsBaseData()
        {}
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
