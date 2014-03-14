#ifndef DMODULE_H
#define DMODULE_H

#include <IOBase.h>
#include <PhysicsBase.h>

struct ModuleData
{
    IOBaseData baseData;
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
