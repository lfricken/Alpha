#include "ForceField.h"

using namespace std;

ForceField::ForceField(ForceFieldData& data) : Module(data.moduleBaseData)
{
    cout << "\nMade one";
}

ForceField::~ForceField()
{
    //dtor
}

bool ForceField::physUpdate()
{
    ///LOOP OVER CONTACTS
    /**still need to filter for distance because it just uses AABB**/
    m_contactList = m_pBody->GetContactList();
    m_hasContact = false;
    while(m_contactList != NULL)
    {
        if(m_contactList->contact->IsTouching())
        {
            m_targetFixture = m_contactList->contact->GetFixtureA();

            if(m_pFixture != m_targetFixture)
                m_target = static_cast<PhysicsBase*>(m_targetFixture->GetBody()->GetUserData());
            else
                m_target = static_cast<PhysicsBase*>(m_contactList->contact->GetFixtureB()->GetBody()->GetUserData());




            m_hasContact = true;
        }
        m_contactList = m_contactList->next;
    }

    return m_hasContact;
}
