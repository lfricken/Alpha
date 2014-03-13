#include "PassiveEventer.h"

using namespace std;

PassiveEventer::PassiveEventer()//finished
{
    m_isActive = false;
}

PassiveEventer::~PassiveEventer()//finished
{
}
void PassiveEventer::event(const string variable)//finished
{
}
bool PassiveEventer::isActive() const//finished
{
    return m_isActive;
}
