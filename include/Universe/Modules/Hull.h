#ifndef MODULE_H
#define MODULE_H

#include "Module.h"

struct HullData;
class Hull : public Module
{
public:
    Hull();
    Hull(const HullData& data);
    virtual ~Hull();

protected:
private:
    void f_initialize(const HullData& data);

};

struct HullData : public ModuleData
{
    HullData() :
        ModuleData()
    {
        type = ClassType::HULL;
        categoryBits = Category::ShipHull;
        maskBits = Mask::ShipHull;
        density = 0;
    }

    virtual Module* generate(Chunk* pChunk)
    {
        std::vector<std::tr1::shared_ptr<ModuleData> > miniList;
        miniList.push_back(std::tr1::shared_ptr<ModuleData>(new ModuleData(*this)));
        ModuleData& rHullSensorData = *miniList.back();
        rHullSensorData.density = 0;
        rHullSensorData.isSensor = true;
        rHullSensorData.categoryBits = Category::ShipHullSensor;
        rHullSensorData.maskBits = Mask::ShipHullSensor;
        rHullSensorData.butes.setBute(Butes::isDestructable, false);
        rHullSensorData.butes.setBute(Butes::isSolid, false);
        pChunk->add(miniList);

        pBody = pChunk->getBody();
        return new Hull(*this);
    }
};

#endif // MODULE_H
