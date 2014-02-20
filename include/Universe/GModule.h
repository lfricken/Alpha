#ifndef DGMODULE_H
#define DGMODULE_H

#include <MultipleInheritance/PhysicsBase.h>
#include <MultipleInheritance/GraphicsBase.h>
#include <MultipleInheritance/IOBase.h>

struct GModuleData
{
    PhysicsBaseData physicsData;
    GraphicsBaseData graphicsData;
};

class GModule : public IOBase, public PhysicsBase, public GraphicsBase
{
public:
    GModule(GModuleData& data);
    GModule(const GModule& old);
    virtual ~GModule();

protected:


private:
};

#endif // DGMODULE_H
