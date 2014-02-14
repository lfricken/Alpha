#ifndef UNIVERSALCONTACTLISTENER_H
#define UNIVERSALCONTACTLISTENER_H
#include <stdafx.h>


class UniversalContactListener : public b2ContactListener
{
    public:
        UniversalContactListener();
        virtual ~UniversalContactListener();

        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
    protected:
    private:
};

#endif // UNIVERSALCONTACTLISTENER_H
