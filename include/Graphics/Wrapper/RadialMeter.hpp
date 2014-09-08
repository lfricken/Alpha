#ifndef RADIALMETER_HPP
#define RADIALMETER_HPP

#include "GraphicsWrapperInterface.hpp"
#include "TriangleFan.hpp"

struct RadialMeterData
{
    RadialMeterData() :
        gfxCompData()
    {
    }

    TriangleFanData gfxCompData;
};

class RadialMeter : public GraphicsWrapperInterface
{
public:
    RadialMeter(const RadialMeterData& rData);
    virtual ~RadialMeter();

    void setPercentFull(float percent);//0-100
    void setAnimState(AnimationState state);

protected:
    TriangleFan* m_pGfxDerived;

private:
};

#endif // RADIALMETER_HPP
