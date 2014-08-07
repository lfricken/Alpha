#ifndef ARMOR_H
#define ARMOR_H

#include "GModule.hpp"

struct AmmoCompartmentData;

class AmmoCompartment : public GModule
{
public:
    AmmoCompartment(const AmmoCompartmentData& rData);
    virtual ~AmmoCompartment();

protected:
private:

};

struct AmmoCompartmentData : public GModuleData
{
    AmmoCompartmentData() :
        GModuleData()
    {
        type = ClassType::STORAGE;
        texName = "textures/ammocompartment/ammocompartment.png";
    }


    virtual GModule* generate(Chunk* pChunk)
    {
        pBody = pChunk->getBody();
        return new AmmoCompartment(*this);
    }
};

#endif // ARMOR_H
