#include "ForceField.h"

using namespace std;

ForceField::ForceField() : Module()
{
    ForceFieldData data;
    f_initialize(data);
}
ForceField::ForceField(const ForceFieldData& data) : Module(static_cast<ModuleData>(data))
{
    f_initialize(data);
}

ForceField::~ForceField()
{

}
void ForceField::f_initialize(const ForceFieldData& data)
{
    m_strength = 400;
}
int ForceField::startContact(PhysicsBase* other)
{
    /**add to list**/
    m_targetBody = static_cast<PhysicsBase*>(other)->getBody();

    ++m_targets[m_targetBody];
    return 0;
}
int ForceField::endContact(PhysicsBase* other)
{
    /**remove from list**/
    m_targetBody = static_cast<PhysicsBase*>(other)->getBody();

    --m_targets[m_targetBody];
    if(m_targets[m_targetBody] == 0)
        m_targets.erase(m_targetBody);

    return 0;
}
bool ForceField::physUpdate()
{
    if(m_isEnabled)
    {
        m_hasContact = false;
        m_ourCoords = m_pBody->GetWorldCenter();

        for(m_it = m_targets.begin(); m_it != m_targets.end(); ++m_it)
        {
            m_targetBody = (m_it->first);

            m_theirCoords = m_targetBody->GetWorldCenter();
            m_theirMass = m_targetBody->GetMass();

            m_direction.x = m_theirCoords.x-m_ourCoords.x;
            m_direction.y = m_theirCoords.y-m_ourCoords.y;
            m_distance = sqrt(m_direction.x*m_direction.x + m_direction.y*m_direction.y);

            m_direction.x = m_direction.x/m_distance;
            m_direction.y = m_direction.y/m_distance;

            m_force.x = m_direction.x*m_theirMass*m_strength*1/m_distance;
            m_force.y = m_direction.y*m_theirMass*m_strength*1/m_distance;

            m_targetBody->ApplyForceToCenter(m_force, true);
            m_pBody->ApplyForceToCenter(-m_force, true);

            m_hasContact = true;
        }
        return m_hasContact;
    }
    return false;
}
void ForceField::enable()
{
    m_isEnabled = true;
}
void ForceField::disable()
{
    m_isEnabled = false;
}
