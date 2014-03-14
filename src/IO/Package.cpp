#include "Package.h"

Package::Package(const std::string& target, const std::string& command, const std::string& parameter, float delay)
{
    reset(target, command, parameter, delay);
    m_targetID = 0;
}

Package::~Package()
{
}
void Package::reset(const std::string& target, const std::string& command, const std::string& parameter, float delay)
{
    m_targetName = target;
    m_command = command;
    m_parameter = parameter;
    m_delay = delay;
}
void Package::doActionOn(IOBase* target) const
{
    if(target != NULL)
        (*target.*m_commandFunction)(m_parameter);
    ///else
        ///ERROR LOG
}
void Package::setTargetID(unsigned int targetID)
{
    m_targetID = targetID;
}
unsigned int Package::getTargetID() const
{
    return m_targetID;
}
float Package::changeTime(const float change)
{
    return m_delay += change;
}
float Package::getTimeRemaining() const
{
    return m_delay;
}
