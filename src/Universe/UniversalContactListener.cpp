#include "UniversalContactListener.h"

void UniversalContactListener::BeginContact(b2Contact* contact)
{
    bool both = false;

    //check if fixture A was a ball
    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if (bodyUserData)
        both = true;

    //check if fixture B was a ball
    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if (bodyUserData && both)
        true;
        ///std::cout << "\nStart Contact!";
}
void UniversalContactListener::EndContact(b2Contact* contact)
{
    bool both = false;
    //check if fixture A was a ball
    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if (bodyUserData)
        both = true;

    //check if fixture B was a ball
    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if (bodyUserData && both)
        true;
        ///std::cout << "\nEnd Contact!";
}
