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
int ForceField::startContact(void* other)
{
    cout << "\nstart";
    return 0;
}
int ForceField::endContact(void* other)
{
    cout << "\nend";
    return 0;
}
int ForceField::preSolveContact(void* other)
{
    cout << "Contacting";
    return 0;
}
int ForceField::postSolveContact(void* other)
{
    cout << "Contacting";
    return 0;
}

bool ForceField::physUpdate()
{
    /*
    if(m_isEnabled)
    {

        m_contactList = m_pBody->GetContactList();
        m_hasContact = false;
        m_ourCoords = m_pBody->GetWorldCenter();

        while(m_contactList != NULL)
        {
       //     cout << "\nContact List != NULL";
            if(m_contactList->contact->IsTouching())
            {
                m_targetBody = m_contactList->contact->GetFixtureA()->GetBody();

                if(m_pBody == m_targetBody)
                    m_targetBody = m_contactList->contact->GetFixtureB()->GetBody();

                m_theirCoords = m_targetBody->GetWorldCenter();
                m_theirMass = m_targetBody->GetMass();

                m_direction.x = m_theirCoords.x-m_ourCoords.x;
                m_direction.y = m_theirCoords.y-m_ourCoords.y;
                m_distance = sqrt(m_direction.x*m_direction.x + m_direction.y*m_direction.y);

                m_direction.x = m_direction.x/m_distance;
                m_direction.y = m_direction.y/m_distance;

                m_force.x = m_direction.x*m_theirMass*m_strength*1/m_distance;
                m_force.y = m_direction.y*m_theirMass*m_strength*1/m_distance;

                m_targetBody->ApplyForceToCenter(m_force, true);///cant apply force?
                m_pBody->ApplyForceToCenter(-m_force, true);

                m_hasContact = true;

            }
            m_contactList = m_contactList->next;

        }
        return m_hasContact;

    }
        */
    return false;

}
