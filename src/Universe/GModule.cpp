#include "GModule.h"
#include "globals.h"
#include "PassiveEventer.h"///this shouldn't be included, like this, check include heirarchy

using namespace sf;

GModule::GModule(const GModuleData& data) : PhysicsBase(data.physicsData, data.baseData), GraphicsBase(data.graphicsData, data.physicsData.halfSize, data.physicsData.offset)
{
    m_pFixture->SetUserData(this);
}
GModule::~GModule()
{
}
bool GModule::damage(int damage)
{
    incTexTile();
    s_health.value -= abs(damage-s_health.armor);
    std::cout << std::endl << s_health.value;
    if(m_spEventer->amount() != 0)
    {
        std::ostringstream convert;   // stream used for the conversion
        convert << s_health.value;      // insert the textual representation of 'Number' in the characters in the stream
        m_spEventer->event(convert.str(), s_health.varName);
    }
    return true;
}
