#include "Reactor.hpp"

Reactor::Reactor(const ReactorData& rData) : GModule(static_cast<GModuleData>(rData)), m_reactorCore(rData.energyProduceRate)
{

}
Reactor::~Reactor()
{

}
bool Reactor::physUpdate()
{
    if(m_isEnabled)
        m_reactorCore.produce(m_pChunk->getEnergyPool());

    GModule::physUpdate();
}
