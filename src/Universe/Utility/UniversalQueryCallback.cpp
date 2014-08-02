#include "UniversalQueryCallback.hpp"
#include "PhysicsBase.hpp"

UniversalQueryCallback::UniversalQueryCallback(b2Body* parentBody)
{
    m_parentBody = parentBody;
}
UniversalQueryCallback::~UniversalQueryCallback()
{

}
bool UniversalQueryCallback::ReportFixture(b2Fixture* fixture)
{
    if((fixture->GetBody() != m_parentBody) && (static_cast<PhysicsBase*>(fixture->GetBody()->GetUserData())->getType() == m_typeFilter))
        m_bodyList.push_back(fixture->GetBody());
    return true;//keep going to find all fixtures in the query area
}
void UniversalQueryCallback::setFilter(ClassType type)
{
    m_typeFilter = type;
}
ClassType UniversalQueryCallback::getFilter() const
{
    return m_typeFilter;
}
std::vector<b2Body*>& UniversalQueryCallback::getBodyList()
{
    return m_bodyList;
}
