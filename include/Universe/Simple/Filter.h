#ifndef FILTER_H
#define FILTER_H

#include "stdafx.h"
#include "ClassType.h"

struct FilterData
{
    FilterData() :
        mustPassAll(false),
        defaultsTrue(true)
    {
    }
    std::map<std::string, bool> names;
    std::map<ClassType, bool> types;
    bool mustPassAll;
    bool defaultsTrue;
};

class Filter
{
public:
    Filter();
    Filter(const FilterData& rData);
    virtual ~Filter();

    bool passes(ClassType type, const std::string& rName) const;
protected:
private:

    std::map<ClassType, bool> m_types;//classname stores the key, bool stores whether it should be allowed or not
    std::map<std::string, bool> m_names;
    bool m_mustPassAll;//do we just have to come back positive on one, or all?
    bool m_default;
};

#endif // FILTER_H
