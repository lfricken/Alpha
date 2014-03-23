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

    if(m_contactList != NULL)
    {
        cout << "Contacting";
        return true;
    }
    else
    {
        return false;
    }
}
