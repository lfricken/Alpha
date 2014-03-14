#include "PassiveEventer.h"

using namespace std;

PassiveEventer::PassiveEventer() : m_isActive(false)
{
}

PassiveEventer::~PassiveEventer()
{
}
void PassiveEventer::event(const string& variable, Variable variableName)
{
}
bool PassiveEventer::isActive() const
{
    return m_isActive;
}
