#include "Condition.h"

/**=====PUBLIC=====**/
Condition::Condition()
{
    ///this shouldn't be the defualt condition
    m_eventName = Event::Health;
    m_stringValue = "99";
    m_intValue = 99;
    m_comparison = '<';
    m_isRepeatable = true;
    f_setComparisonFunction(m_comparison);
}
Condition::Condition(Event eventName, const std::string& stringVar, int intVar, char comparison, bool repeatable)
{
    reset(eventName, stringVar, intVar, comparison, repeatable);
}
Condition::~Condition() {}
void Condition::reset(Event eventName, const std::string& stringValue, int intValue, char comparison, bool repeatable)
{
    m_eventName = eventName;
    m_stringValue = stringValue;
    m_intValue = intValue;
    m_comparison = comparison;
    m_isRepeatable = repeatable;
    f_setComparisonFunction(comparison);
}
char Condition::getComparison() const
{
    return m_comparison;
}
Event Condition::getEventName() const
{
    return m_eventName;
}
bool Condition::evaluate(const std::string& input) const
{
    return (*this.*m_evaluationFunction)(input);
}
bool Condition::isRepeatable() const
{
    return m_isRepeatable;
}

/**=====PRIVATE=====**/
bool Condition::f_greaterThan(const std::string& input) const
{
    return (atoi(input.c_str()) > m_intValue);
}
bool Condition::f_lessThan(const std::string& input) const
{
    return (atoi(input.c_str()) < m_intValue);
}
bool Condition::f_equals(const std::string& input) const
{
    if(atoi(input.c_str()) == m_intValue)
        return true;
    else if (input == m_stringValue)
        return true;
    else
        return false;
}
bool Condition::f_notEquals(const std::string& input) const
{
    if(atoi(input.c_str()) == m_intValue)//check if they are equal
        return false;
    else if (input == m_stringValue)
        return false;
    else
        return true;
}
bool Condition::f_change(const std::string& input) const
{
    return true;
}
void Condition::f_setComparisonFunction(char op)
{
    if (op == '>')
        m_evaluationFunction = &Condition::f_greaterThan;
    else if (op == '<')
        m_evaluationFunction = &Condition::f_lessThan;
    else if (op == '=')
        m_evaluationFunction = &Condition::f_equals;
    else if (op == '!')
        m_evaluationFunction = &Condition::f_notEquals;
    else if (op == 'd')
        m_evaluationFunction = &Condition::f_change;
    else
    {
        std::cout << "\nERROR: " << FILELINE;
        m_evaluationFunction = &Condition::f_equals;//default to equals
        ///ERROR LOG
    }
}
