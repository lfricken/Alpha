#include "Package.h"
#include "IOBase.h"
#include "globals.h"

#include "Enumerate.h"

Package::Package()
{
    sf::Packet tempParam;
    tempParam << 0;
    reset("player_1", "default", tempParam, 0.0, Destination::UNIVERSE);
}
Package::Package(const std::string& target, const std::string& command, const sf::Packet& parameter, float delay, Destination dest)
{
    reset(target, command, parameter, delay, dest);
}

Package::~Package()
{
}
void Package::reset(const std::string& target, const std::string& command, const sf::Packet& parameter, float delay, Destination dest)
{
    m_targetName = target;
    m_command = command;
    m_parameter = parameter;
    m_delay = delay;
    m_destination = dest;
    m_targetID = 0;//default until assigned
}
/**SETTERS**/
void Package::setTargetID(unsigned int targetID)
{
    m_targetID = targetID;
}
void Package::setTargetName(const std::string& targetName)
{
    m_targetName = targetName;
}
void Package::setParameter(const sf::Packet& parameter)
{
    m_parameter = parameter;
}

/**GETTERS**/
float Package::getDelay() const
{
    return m_delay;
}
unsigned int Package::getTargetID() const
{
    return m_targetID;
}
const sf::Packet& Package::getParameter() const
{
    return m_parameter;
}
const std::string& Package::getTargetName() const
{
    return m_targetName;
}
const std::string& Package::getCommand() const
{
    return m_command;
}
Destination Package::getDestination() const
{
    return m_destination;
}
/**GETTERS**/
