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
    m_guests.push_back(pOther);
    return 0;
}
int ForceField::endContact(PhysicsBase* pOther)
{
    /**remove from list**/
    bool error = true;
    for(unsigned int i = 0; i<m_guests.size(); ++i)
    {
        if(pOther == m_guests[i])
        {
            m_guests.erase(m_guests.begin()+i);
            error = false;
            break;
        }
    }
    if(error)
        cout << "\nMAJOR WTF MOMENt";
    return 0;
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
