#ifndef PACKAGE_H
#define PACKAGE_H

#include "stdafx.h"
#include "ClassType.h"

class IOBase;

typedef ClassType Destination;

typedef void (IOBase::*CommandFunction)(sf::Packet&);
class Package
{
public:
    Package();
    Package(const std::string& target, const std::string& command, const sf::Packet& parameter, float delay, Destination dest);
    ~Package();
    void reset(const std::string& target, const std::string& command, const sf::Packet& parameter, float delay, Destination dest);

  ///  void setTargetID(unsigned int targetID);

    const std::string& getTargetName();
    float getDelay() const;
    unsigned long long int getTargetID() const;
    CommandFunction getComFunc() const;
    Destination getDestination() const;
    sf::Packet& getParameter();

private:
    std::string m_targetName;//used initially to get targetID
    std::string m_command;//used to
    sf::Packet m_parameter;//addition information used to do the action, such as set health to the parameter
    float m_delay;//delay used by IO manager, to wait that many seconds to send it to the target
    Destination m_destination;

    /**INITIALIZED AFTER CREATION**/
    unsigned long long int m_targetID;//used to do binary search for object, after everything is loaded into mem, have someone do setTargetIDs()
    CommandFunction m_commandFunction;
};

struct Packagelet///WTF IS THIS???
{
    Packagelet() {}
    Packagelet(float time, unsigned long long int target, CommandFunction command, Destination dest, sf::Packet& param)
        : timeRemaining(time), targetID(target), commandFunction(command), destination(dest),parameter(param) {}
        /**
    Packagelet(const Packagelet& old)
    {
        timeRemaining = old.timeRemaining;
        targetID = old.targetID;
        commandFunction = old.commandFunction;
        parameter = old.parameter;
    }
    Packagelet& operator= (const Packagelet& old)
    {
        timeRemaining = old.timeRemaining;
        targetID = old.targetID;
        commandFunction = old.commandFunction;
        parameter = old.parameter;
        return *this;
    }
**/
    float timeRemaining;
    unsigned long long int targetID;
    CommandFunction commandFunction;
    Destination destination;
    sf::Packet parameter;
};

#endif // PACKAGE_H
