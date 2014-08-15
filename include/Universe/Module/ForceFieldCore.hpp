#ifndef FORCEFIELDCORE_H
#define FORCEFIELDCORE_H

#include "GModule.hpp"
#include "ForceField.hpp"

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
        pForceField(NULL)
    {
        type = ClassType::FORCE;
        categoryBits = Category::ShipModule;
        maskBits = Mask::ShipModuleNorm;
        texName = "textures/force_field_core/force_field_core_1.png";
        animationFileName = "textures/force_field_core/force_field_core_1.acfg";
    }

    ForceField* pForceField;
    ForceFieldData forceFieldData;


    virtual GModule* generate(Chunk* pChunk) const
    {


        std::vector<std::tr1::shared_ptr<const ModuleData> > fieldDataList;
        fieldDataList.push_back(std::tr1::shared_ptr<const ModuleData>(new ForceFieldData(forceFieldData)));
        ForceField* ptr = dynamic_cast<ForceField*>(pChunk->add(fieldDataList));
        if(ptr == NULL)
        {
            ///ERROR LOG
            std::cout << FILELINE;
        }


        ForceFieldCoreData mutableCopy(*this);
        mutableCopy.pBody = pChunk->getBody();
        mutableCopy.pForceField = ptr;
                mutableCopy.pChunk = pChunk;
        return new ForceFieldCore(mutableCopy);
    }
};
#endif // FORCEFIELDCORE_H
