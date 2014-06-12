#ifndef FORCEFIELDCORE_H
#define FORCEFIELDCORE_H

#include "GModule.h"
#include "ForceField.h"

struct ForceFieldCoreData : public GModuleData
{
    ForceFieldCoreData() :
        GModuleData(),
        pForceField(NULL),
        fieldData()
    {
        type = ClassType::FORCE;
        categoryBits = Category::ShipModule;
        maskBits = Mask::ShipModuleNorm;
        texName = "textures/force_field_core/force_field_core_1.png";
    }

    ForceField* pForceField;
    ForceFieldData fieldData;
};

class ForceFieldCore : public GModule
{
    public:
        ForceFieldCore();
        virtual ~ForceFieldCore();
        ForceFieldCore(const ForceFieldCoreData& data);


        virtual void destruct();

    protected:
    private:
        void f_initialize(const ForceFieldCoreData& data);

        ForceField* m_pForceField;//we don't own this

};

#endif // FORCEFIELDCORE_H
