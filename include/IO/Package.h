#ifndef PACKAGE_H
#define PACKAGE_H

#include "stdafx.h"
class IOBase;

class Package
{
public:
    Package(const std::string& target, const std::string& command, const std::string& parameter, float delay);
    ~Package();
    void reset(const std::string& target, const std::string& command, const std::string& parameter, float delay);

    void doActionOn(IOBase* target) const;
    void setTargetID(unsigned int targetID);
    unsigned int getTargetID() const;

    float changeTime(const float timeChange);
    float getTimeRemaining() const;
private:
    std::string m_targetName;//used initially to get targetID
    std::string m_command;//used to
    std::string m_parameter;//addition information used to do the action, such as set health to the parameter
    float m_delay;//delay used by IO manager, to wait that many seconds to send it to the target

    /**INITIALIZED AFTER CREATION**/
    unsigned int m_targetID;//used to do binary search for object, after everything is loaded into mem, have someone do setTargetIDs()
    typedef void (IOBase::*CommandFunction)(const std::string&);
    CommandFunction m_commandFunction;
};

#endif // PACKAGE_H
