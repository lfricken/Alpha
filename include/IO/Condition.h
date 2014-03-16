#ifndef CONDITION_H
#define CONDITION_H

#include "VariableNames.h"

class Condition//used to determine if the package should be sent
{
public:
    Condition();
    Condition(Variable varName, const std::string& stringValue, float floatValue, char comparison, bool repeatable);
    virtual ~Condition();
    void reset(Variable varName, const std::string& stringValue, float floatValue, char comparison, bool repeatable);

    Variable getVariableName() const;
    bool evaluate(const std::string& input) const;
    bool isRepeatable() const;

private:
    bool f_greaterThan(const std::string& input) const;
    bool f_lessThan(const std::string& input) const;
    bool f_equals(const std::string& input) const;
    bool f_notEquals(const std::string& input) const;
    bool f_change(const std::string& input) const;
    void f_setComparisonFunction(char op);

    typedef bool (Condition::*ComparisonFunction)(const std::string&) const;
    ComparisonFunction m_evaluationFunction;

    Variable m_variableName;
    std::string m_stringValue;//the value to compare to the current variable
    float m_floatValue;//incase its a numerical value, we can put it in here when this is created
    char m_comparison;//character type used to compare, so it could be >, <, or =
    bool m_isRepeatable;//used by the Eventer to decide whether to keep this Courier after it got activated once
};

#endif // CONDITION_H
