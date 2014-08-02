#ifndef REACTOR_H
#define REACTOR_H

#include "GModule.hpp"
#include "ReactorComponent.hpp"
struct ReactorData;


/**produces energy for our energy pool**/
class Reactor : public GModule
{
public:
    Reactor(const ReactorData& rData);
    virtual ~Reactor();

    bool physUpdate();

protected:
private:
    ReactorComponent m_reactorCore;
};

struct ReactorData : public GModuleData
{
    ReactorData() :
        GModuleData(),
        energyProduceRate(1)
    {
        type = ClassType::REACTOR;
        texName = "textures/reactor/reactor.png";
    }

    T_Energy energyProduceRate;

    virtual GModule* generate(Chunk* pChunk)
    {
        pBody = pChunk->getBody();
        return new Reactor(*this);
    }
};

#endif // REACTOR_H
