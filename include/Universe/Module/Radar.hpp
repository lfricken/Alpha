#ifndef RADAR_H
#define RADAR_H

#include "GModule.hpp"
#include "Spinner.hpp"
#include "ZoomModComponent.hpp"

struct RadarData;

class Radar : public GModule
{
public:
    Radar(const RadarData& rData, std::tr1::shared_ptr<ZoomPool> spZPool);
    virtual ~Radar();

protected:
    void animatePreHook();
    void enablePostHook();
    void disablePostHook();

private:
    ///make radar actually add to the max zoom pool through a zoom component
    ZoomModComponent m_zoomComponent;
    Spinner m_dish;
    std::tr1::shared_ptr<ZoomPool> m_spZoomPool;
};

struct RadarData : public GModuleData
{
    RadarData() :
        GModuleData(),
        zoomMult(2),
        dishData()
    {
        dishData.spinRate = 45;
        dishData.decorData.gfxCompData.texName = "textures/radar/dish.png";
        dishData.decorData.gfxCompData.scale = sf::Vector2f(1,1);
        type = ClassType::SENSOR;
        texTileSize = sf::Vector2f(256,256);
        texName = "textures/radar/base.png";
    }

    T_Zoom zoomMult;
    SpinnerData dishData;

    virtual GModule* generate(Chunk* pChunk) const
    {
        RadarData mutableCopy(*this);
        mutableCopy.pBody = pChunk->getBody();
        mutableCopy.pChunk = pChunk;
        return new Radar(mutableCopy, pChunk->getZoomPoolSPtr());
    }
};

#endif // RADAR_H
