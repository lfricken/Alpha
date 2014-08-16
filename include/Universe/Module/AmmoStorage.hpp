#ifndef AMMOSTORAGE_H
#define AMMOSTORAGE_H

#include "GModule.hpp"
#include "CapacityChanger.hpp"
#include "TriangleFan.h"

struct AmmoStorageData;

class AmmoStorage : public GModule
{
public:
    AmmoStorage(const AmmoStorageData& rData);
    virtual ~AmmoStorage();

    void animatePreHook();
    void enablePostHook();
    void disablePostHook();

protected:
private:
    AmmoType m_ammoType;
    CapacityChanger<T_Ammo> m_capacity;

    TriangleFan* m_pAmmoFill;
    std::tr1::shared_ptr<AmmoGroup> m_spAmmoGroup;
};


struct AmmoStorageData : public GModuleData
{
    AmmoStorageData() :
        GModuleData(),
        ammoType(AmmoType::MediumShell),
        capacity(50),
        comesWith(30)

    {
        type = ClassType::STORAGE;
        texName = "textures/storage/storage.png";
        animationFileName = "textures/storage/storage.acfg";
        fillData.texName = "textures/fill/black.png";
    }

    AmmoType ammoType;
    T_Ammo capacity;
    T_Ammo comesWith;
    TriangleFanData fillData;

    virtual GModule* generate(Chunk* pChunk) const
    {
        AmmoStorageData mutableCopy(*this);
        mutableCopy.pBody = pChunk->getBody();
        mutableCopy.pChunk = pChunk;
        return new AmmoStorage(mutableCopy);
    }
};

#endif // AMMOSTORAGE_H
