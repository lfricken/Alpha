#include "ForceField.h"

using namespace std;

ForceField::ForceField() : Module()
{
    ForceFieldData data;
    f_initialize(data);
}
ForceField::ForceField(const ForceFieldData& rData) : Module(static_cast<ModuleData>(rData))
{
    f_initialize(rData);
}

ForceField::~ForceField()
{

}
void ForceField::f_initialize(const ForceFieldData& rData)
{
    m_strength = rData.forceStrength;
}
int ForceField::startContact(PhysicsBase* pOther)
{
    /**add to list**/
    m_targetBody = static_cast<PhysicsBase*>(pOther)->getBody();

    ++m_targets[m_targetBody];
    return 0;
}
int ForceField::endContact(PhysicsBase* pOther)
{
    /**remove from list**/
    m_targetBody = static_cast<PhysicsBase*>(pOther)->getBody();

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
