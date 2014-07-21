#include "Filter.h"

Filter::Filter()
{
    m_mustPassAll = false;
    m_default = false;
}
Filter::Filter(const FilterData& rData)
{
    m_names = rData.names;
    m_types = rData.types;
    m_mustPassAll = rData.mustPassAll;
    m_default = rData.defaultsTrue;
}
Filter::~Filter()
{

}
bool Filter::passes(ClassType type, const std::string& rName) const
{
    bool passedType;
    bool passedName;

    auto it_type = m_types.find(type);
    if(it_type == m_types.end())//the key doesn't exist
        passedType = m_default;//so it defaults to pass
    else
        passedType = it_type->second;


    auto it_name = m_names.find(rName);
    if(it_name == m_names.end())//the key doesn't exist
        passedName = m_default;//so it defaults to pass
    else
        passedName = it_name->second;


    if(m_mustPassAll)
        return (passedType && passedName);
    else
        return (passedType || passedName);
}
