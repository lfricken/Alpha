#include "ForceField.h"

using namespace std;

ForceField::ForceField(ForceFieldData& data) : Module(data.moduleBaseData)
{
    m_strength = 400;
}

ForceField::~ForceField()
{

}
bool ForceField::physUpdate()
{
    if(m_isEnabled)
    {

        m_contactList = m_pBody->GetContactList();
        m_hasContact = false;
        m_ourCoords = m_pBody->GetWorldCenter();

        while(m_contactList != NULL)
        {
        if(m_contactList->contact->IsTouching())
            return false;
            /**
            if(m_contactList->contact->IsTouching())
            {

                m_targetFixture = m_contactList->contact->GetFixtureA();

                if(m_pFixture != m_targetFixture)
                    m_target = static_cast<PhysicsBase*>(m_targetFixture->GetUserData());
                else
                    m_target = static_cast<PhysicsBase*>(m_contactList->contact->GetFixtureB()->GetUserData());
                m_theirCoords = m_target->getBody().GetWorldCenter();
                m_theirMass = m_target->getBody().GetMass();
                m_direction.x = m_theirCoords.x-m_ourCoords.x;
                m_direction.y = m_theirCoords.y-m_ourCoords.y;
                m_distance = sqrt(m_direction.x*m_direction.x + m_direction.y*m_direction.y);

                m_direction.x = m_direction.x/m_distance;
                m_direction.y = m_direction.y/m_distance;

                m_force.x = m_direction.x*m_theirMass*m_strength*1/m_distance;
                m_force.y = m_direction.y*m_theirMass*m_strength*1/m_distance;

                m_target->getBody().ApplyForceToCenter(m_force, true);
                m_pBody->ApplyForceToCenter(-m_force, true);

                m_hasContact = true;

            }
            m_contactList = m_contactList->next;
                            **/


        }

        return m_hasContact;

    }
    return false;
}
