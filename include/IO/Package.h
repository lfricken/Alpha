#ifndef PACKAGE_H
#define PACKAGE_H

#include "stdafx.h"
#include "ClassType.h"

class IOBase;

typedef ClassType Destination;///ISNT USED FOR ANYTHING AT THE MOMENT

class Package
{
public:
    Package();
    Package(const std::string& target, const std::string& command, const sf::Packet& parameter, float delay, Destination dest);
    ~Package();
    void reset(const std::string& target, const std::string& command, const sf::Packet& parameter, float delay, Destination dest);


    /**SETTERS**/
    void setTargetID(unsigned int targetID);
    void setTargetName(const std::string& targetName);
    void setParameter(const sf::Packet& parameter);


    /**GETTERS**/
    const std::string& getTargetName() const;
    const std::string& getCommand() const;
    float getDelay() const;
    unsigned int getTargetID() const;
    Destination getDestination() const;
    const sf::Packet& getParameter() const;

private:
    std::string m_targetName;//used initially to get targetID
    std::string m_command;//used to
    sf::Packet m_parameter;//addition information used to do the action, such as set health to the parameter
    float m_delay;//delay used by IO manager, to wait that many seconds to send it to the target
    Destination m_destination;

    /**INITIALIZED AFTER CREATION**/
    unsigned int m_targetID;//used to do binary search for object, after everything is loaded into mem, have someone do setTargetIDs()
    std::string m_commandFunction;
};

struct Packagelet//used inside IOManager for storing the package data till it's ready to be sent
{
    Packagelet() {}
    Packagelet(float time, unsigned int target, const std::string& inCommand, Destination dest, const sf::Packet& param)
        : timeRemaining(time), targetID(target), command(inCommand), destination(dest), parameter(param), done(false) {}

    float timeRemaining;
    unsigned int targetID;
    std::string command;
    Destination destination;
    sf::Packet parameter;
    bool done;
};

#endif // PACKAGE_H
