#ifndef DGMODULE_H
#define DGMODULE_H

#include <MultipleInheritance/PhysicsBase.h>
#include <MultipleInheritance/GraphicsBase.h>
#include <MultipleInheritance/IOBase.h>

struct DGModuleData
{
    PhysicsBaseData physicsData;
    GraphicsBaseData graphicsData;
};

class DGModule : public IOBase, public PhysicsBase, public GraphicsBase
{
public:
    DGModule(DGModuleData& data);
    DGModule(const DGModule& old);
    virtual ~DGModule();

protected:


private:
};

#endif // DGMODULE_H
