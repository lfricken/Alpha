#ifndef FORCEFIELDCORE_H
#define FORCEFIELDCORE_H

#include "GModule.hpp"
#include "ForceField.hpp"

struct ForceFieldCoreData;///WE NEED TO CONSUME ENERGY
class ForceFieldCore : public GModule
{
    public:
        virtual ~ForceFieldCore();
        ForceFieldCore(const ForceFieldCoreData& data);


        virtual void destruct();
        virtual void special_1();
        virtual bool physUpdate();

    protected:
        virtual void enablePostHook();
        virtual void disablePostHook();
        virtual void animatePreHook();


    private:
        Decoration m_fieldDecor;
        ForceField* m_pForceField;//we don't own this
        float m_energyConsumption;//consume per second
        Timer m_cooldown;//timer to prevent rapid on off-ing

};
struct ForceFieldCoreData : public GModuleData
{
    ForceFieldCoreData() :
        GModuleData(),
        pForceField(NULL),
        energyConsumption(5),
        cooldown(1)
    {
        type = ClassType::FORCE;
        categoryBits = Category::ShipModule;
        maskBits = Mask::ShipModuleNorm;
        texName = "textures/force_field_core/force_field_core_1.png";
        animationFileName = "textures/force_field_core/force_field_core_1.acfg";

        m_fieldDecorDat.gfxCompData.animationFileName = "textures/force_field/field.acfg";
        m_fieldDecorDat.gfxCompData.texName = "textures/force_field/field.png";
        m_fieldDecorDat.gfxCompData.gfxLayer = GraphicsLayer::Shield;
    }

    ForceField* pForceField;
    ForceFieldData forceFieldData;
    DecorationData m_fieldDecorDat;
    float energyConsumption;
    float cooldown;


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

        mutableCopy.m_fieldDecorDat.gfxCompData.dimensions.x = 2*scale*forceFieldData.halfSize.x;
        mutableCopy.m_fieldDecorDat.gfxCompData.dimensions.y = 2*scale*forceFieldData.halfSize.y;

        std::cout << "\n" <<  2*scale*forceFieldData.halfSize.x;

        return new ForceFieldCore(mutableCopy);
    }
};
#endif // FORCEFIELDCORE_H
