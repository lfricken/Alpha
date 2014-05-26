#ifndef UNIVERSALQUERYCALLBACK_H
#define UNIVERSALQUERYCALLBACK_H

#include "stdafx.h"
#include "ClassType.h"

class UniversalQueryCallback : public b2QueryCallback
{
    public:
        UniversalQueryCallback(b2Body* parentBody);
        virtual ~UniversalQueryCallback();

        bool ReportFixture(b2Fixture* fixture);

        std::vector<b2Body*>& getBodyList();
        void setFilter(ClassType type);
        ClassType getFilter() const;
    protected:
    private:
        b2Body* m_parentBody;
        std::vector<b2Body*> m_bodyList;
        ClassType m_typeFilter;///should make more advanced filters? //used to only look for this type of class
};

#endif // UNIVERSALQUERYCALLBACK_H
