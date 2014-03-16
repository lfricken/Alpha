#include "Package.h"
#include "IOBase.h"


Package::Package()
{
    m_targetName = "player_1";
    m_command = "default";
    m_parameter << 0;
    m_delay = 0;
    m_commandFunction = &IOBase::input_1;
    m_targetID = 1;
}
Package::Package(const std::string& target, const std::string& command, sf::Packet& parameter, float delay)
{
    reset(target, command, parameter, delay);
}

Package::~Package()
{
}
void Package::reset(const std::string& target, const std::string& command, sf::Packet& parameter, float delay)
{
    m_targetName = target;
    m_command = command;
    m_parameter = parameter;
    m_delay = delay;
    ///if(command = anything in the list of input1)
        m_commandFunction = &IOBase::input_1;
    ///else
    m_targetID = 0;
}
void Package::setTargetID(unsigned int targetID)
{
    m_targetID = targetID;
}
float Package::getDelay() const
{
    return m_delay;
}
unsigned int Package::getTargetID() const
{
    return m_targetID;
}
CommandFunction Package::getComFunc() const
{
    return m_commandFunction;
}
sf::Packet& Package::getParameter()
{
    return m_parameter;
}
