#ifndef DGMODULE_H
#define DGMODULE_H

#include <MultipleInheritance/PhysicsBase.h>
#include <MultipleInheritance/GraphicsBase.h>
#include <MultipleInheritance/IOBase.h>

struct GModuleData : public Data
{
    PhysicsBaseData physicsData;
    GraphicsBaseData graphicsData;
};

class GModule : public PhysicsBase, public GraphicsBase
{
public:
    GModule(GModuleData& data);
    GModule(const GModule& old);///may be obsolete, and bad
    virtual ~GModule();

    virtual bool input(Package& rPackage);

protected:


private:
};

#endif // DGMODULE_H
