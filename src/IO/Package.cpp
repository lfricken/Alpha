#include "Package.h"
#include "IOBase.h"
#include "BaseFunctionFinder.h"
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
    m_targetID = Enumerate(m_targetName);
    m_destination = dest;

    m_commandFunction = game.getGameFunctionFinder().getFunction(command);
}
/*
void Package::setTargetID(unsigned int targetID)
{
    m_targetID = targetID;
}
*/
float Package::getDelay() const
{
    return m_delay;
}
unsigned long long int Package::getTargetID() const
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
const std::string& Package::getTargetName()
{
    return m_targetName;
}
Destination Package::getDestination() const
{
    return m_destination;
}
