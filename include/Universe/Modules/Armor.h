#ifndef ARMOR_H
#define ARMOR_H

#include "GModule.h"

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
    }


    virtual GModule* generate(Chunk* pChunk)
    {
        pBody = pChunk->getBody();
        return new Armor(*this);
    }
};

#endif // ARMOR_H
