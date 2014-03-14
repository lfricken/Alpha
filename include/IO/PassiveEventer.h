#ifndef PassiveEventer_H
#define PassiveEventer_H

#include "stdafx.h"
#include "IOBase.h"
#include "VariableNames.h"

class PassiveEventer//look at ActiveEventer for details.
{
public:
    PassiveEventer();
    virtual ~PassiveEventer();

    virtual void event(const std::string& variable, Variable variableName);

    virtual bool isActive() const;
protected:
    bool m_isActive;
private:
};

#endif // PassiveEventer_H
