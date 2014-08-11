#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "GModule.hpp"
#include "CapacitorComponent.hpp"

struct CapacitorData;

class Capacitor : public GModule
{
public:
    Capacitor(const CapacitorData& rData, std::tr1::shared_ptr<EnergyPool> spEpool);
    virtual ~Capacitor();

protected:
    void animatePreHook();
    void enablePostHook();
    void disablePostHook();

private:
    ///FILL METER

    CapacitorComponent m_capacity;
    std::tr1::shared_ptr<EnergyPool> m_spEnergyPool;
};

struct CapacitorData : public GModuleData
{
    CapacitorData() :
        GModuleData(),
        energyStorage(100)
    {
        type = ClassType::CAPACITOR;
        texTileSize = sf::Vector2f(256,256);
        texName = "textures/capacitor/capacitor.png";
        animationFileName = "textures/capacitor/capacitor.acfg";
    }

    T_Energy energyStorage;


    virtual GModule* generate(Chunk* pChunk) const
    {
        CapacitorData mutableCopy(*this);
        mutableCopy.pBody = pChunk->getBody();
                mutableCopy.pChunk = pChunk;
        return new Capacitor(mutableCopy, pChunk->getEnergyPoolSPtr());
    }
};
#endif // CAPACITOR_H
