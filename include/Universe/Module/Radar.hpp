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
        dishData.spinRate = 45;
        dishData.decorData.gfxCompData.texName = "textures/radar/dish.png";
        dishData.decorData.gfxCompData.animationFileName = "textures/radar/dish.acfg";
        dishData.decorData.gfxCompData.scale = sf::Vector2f(1,1);
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
