#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "GModule.hpp"
#include "CapacitorComponent.hpp"

struct CapacitorData;

class Capacitor : public GModule
{
public:
    Capacitor(const CapacitorData& rData);
    virtual ~Capacitor();

    void enable();
    void disable();

protected:
private:
    CapacitorComponent m_capacity;
};

struct CapacitorData : public GModuleData
{
    CapacitorData() :
        GModuleData(),
        energyStorage(100)
    {
        type = ClassType::CAPACITOR;
        texName = "textures/capacitor/capacitor.png";
    }

    T_Energy energyStorage;

    virtual GModule* generate(Chunk* pChunk)
    {
        pBody = pChunk->getBody();
        return new Capacitor(*this);
    }
};
#endif // CAPACITOR_H
