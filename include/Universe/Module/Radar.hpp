#ifndef RADAR_H
#define RADAR_H

#include "GModule.hpp"
#include "Spinner.hpp"
#include "CapacityChanger.hpp"

struct RadarData;

class Radar : public GModule
{
public:
    Radar(const RadarData& rData);
    virtual ~Radar();

protected:
    void animatePreHook();
    void enablePostHook();
    void disablePostHook();

private:
    CapacityChanger<T_Zoom> m_zoomComponent;
    Spinner m_dish;
    std::tr1::shared_ptr<ZoomPool> m_spZoomPool;
};

struct RadarData : public GModuleData
{
    RadarData() :
        GModuleData(),
        zoomAdd(1),
        dishData()
    {
        dishData.minRate = 45;
        dishData.gfxCompData.texName = "textures/radar/dish.png";
        dishData.gfxCompData.animationFileName = "textures/radar/dish.acfg";
        dishData.gfxCompData.dimensions = sf::Vector2f(128,128);
        type = ClassType::SENSOR;
        animationFileName = "textures/radar/base.acfg";
        texName = "textures/radar/base.png";
    }

    T_Zoom zoomAdd;
    SpinnerData dishData;

    virtual GModule* generate(Chunk* pChunk) const
    {
        RadarData mutableCopy(*this);
        mutableCopy.pBody = pChunk->getBody();
        mutableCopy.pChunk = pChunk;
        return new Radar(mutableCopy);
    }
};

#endif // RADAR_H
