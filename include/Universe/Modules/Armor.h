#ifndef ARMOR_H
#define ARMOR_H

#include "GModule.h"

struct ArmorData;
class Armor : public GModule
{
public:
    Armor();
    Armor(const ArmorData& rData);
    virtual ~Armor();

protected:
private:
    void f_initialize(const ArmorData& rData);

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
