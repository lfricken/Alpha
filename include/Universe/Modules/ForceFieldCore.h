#ifndef FORCEFIELDCORE_H
#define FORCEFIELDCORE_H

#include "GModule.h"
#include "ForceField.h"

struct ForceFieldCoreData;
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
struct ForceFieldCoreData : public GModuleData
{
    ForceFieldCoreData() :
        GModuleData(),
        pForceField(NULL),
        spForceFieldData(new ForceFieldData())
    {
        type = ClassType::FORCE;
        categoryBits = Category::ShipModule;
        maskBits = Mask::ShipModuleNorm;
        texName = "textures/force_field_core/force_field_core_1.png";
    }

    ForceField* pForceField;
    std::tr1::shared_ptr<ForceFieldData> spForceFieldData;


    virtual GModule* generate(Chunk* pChunk)
    {
        std::vector<std::tr1::shared_ptr<ModuleData> > fieldDataList;
        fieldDataList.push_back(spForceFieldData);
        pForceField = dynamic_cast<ForceField*>(pChunk->add(fieldDataList));
        if(pForceField == NULL)
        {
            ///ERROR LOG
            std::cout << FILELINE;
        }

        pBody = pChunk->getBody();
        return new ForceFieldCore(*this);
    }
};
#endif // FORCEFIELDCORE_H
