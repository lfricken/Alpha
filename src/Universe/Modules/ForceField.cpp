#include "ForceField.h"

using namespace std;

ForceField::ForceField() : Trigger()
{
    ForceFieldData data;
    f_initialize(data);
}
ForceField::ForceField(const ForceFieldData& rData) : Trigger(static_cast<TriggerData>(rData))
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
bool ForceField::physUpdate()
{
    bool hasContact = false;

    if(m_isEnabled)
    {
        for(auto it = m_guests.begin(); it != m_guests.end(); ++it)
        {

            float distanceMagnitude;
            b2Vec2 force;
            b2Vec2 difference;
            b2Vec2 direction;
            b2Vec2 ourCoords = m_pBody->GetWorldCenter();
            PhysicsBase* targetPhysBase = *it;
            b2Vec2 theirCoords = targetPhysBase->getFixture()->GetBody()->GetWorldCenter();
            float theirMass = targetPhysBase->getFixture()->GetBody()->GetMass();

            difference = theirCoords-ourCoords;
            distanceMagnitude = difference.Length();
            direction = difference;
            direction.Normalize();


            force.x = direction.x*theirMass*m_strength*1/distanceMagnitude;
            force.y = direction.y*theirMass*m_strength*1/distanceMagnitude;

            targetPhysBase->getFixture()->GetBody()->ApplyForceToCenter(force, true);
            m_pBody->ApplyForceToCenter(-force, true);

            hasContact = true;
        }
    }
    return hasContact;
}
