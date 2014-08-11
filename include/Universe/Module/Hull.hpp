#ifndef MODULE_H
#define MODULE_H

#include "Module.hpp"

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

    virtual Module* generate(Chunk* pChunk) const
    {
        std::vector<std::tr1::shared_ptr<const ModuleData> > miniList;
        ModuleData rHullSensorData(*this);
        rHullSensorData.density = 0;
        rHullSensorData.isSensor = true;
        rHullSensorData.categoryBits = Category::ShipHullSensor;
        rHullSensorData.maskBits = Mask::ShipHullSensor;
        rHullSensorData.butes.setBute(Butes::isDestructable, false);
        rHullSensorData.butes.setBute(Butes::isSolid, false);
        miniList.push_back(std::tr1::shared_ptr<const ModuleData>(new ModuleData(rHullSensorData)));
        pChunk->add(miniList);

        HullData mutableCopy(*this);
        mutableCopy.pBody = pChunk->getBody();
        mutableCopy.pChunk = pChunk;
        return new Hull(mutableCopy);
    }
};

#endif // MODULE_H
