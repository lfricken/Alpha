#include "UniversalContactListener.h"

void UniversalContactListener::BeginContact(b2Contact* contact)
{
    bool both = false;


    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if (bodyUserData)
        both = true;

    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if (bodyUserData && both)
        true;
        ///std::cout << "\nStart Contact!";
}
void UniversalContactListener::EndContact(b2Contact* contact)
{
    bool both = false;


    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if (bodyUserData)
        both = true;


    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if (bodyUserData && both)
        true;
        ///std::cout << "\nEnd Contact!";
}
