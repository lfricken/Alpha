#ifndef ARMOR_H
#define ARMOR_H

#include "GModule.hpp"

struct ArmorData;

class Armor : public GModule
{
public:
    Armor(const ArmorData& rData);
    virtual ~Armor();

protected:
private:

};

struct ArmorData : public GModuleData
{
    ArmorData() :
        GModuleData()
    {
        type = ClassType::ARMOR;
        armor = 500;
        texName = "textures/armor/armor.png";
        animationFileName = "textures/armor/armor.acfg";
    }


    virtual GModule* generate(Chunk* pChunk) const
    {
        ArmorData mutableCopy(*this);
        mutableCopy.pBody = pChunk->getBody();
        mutableCopy.pChunk = pChunk;
        return new Armor(mutableCopy);
    }
};

#endif // ARMOR_H
