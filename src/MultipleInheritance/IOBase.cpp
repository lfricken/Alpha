#include "IOBase.h"
#include "globals.h"
#include "IOManager.h"

#include "Enumerate.h"

using namespace std;

IOBase::IOBase() : m_rIOManager(game.getGameIOManager())
{
    IOBaseData data;
    f_initialize(data);
}
IOBase::IOBase(const IOBaseData& data) : m_rIOManager(game.getGameIOManager())
{
    f_initialize(data);
}
IOBase::~IOBase()
{
    m_pIOComponent->free();
}
void IOBase::f_initialize(const IOBaseData& data)
{
    m_pIOComponent = m_rIOManager.createIOComponent(data.name);
    m_pIOComponent->setOwner(this);
    m_pIOComponent->getEventer()->addList(data.spCourierList);

    m_attributes = data.butes;

    m_type = data.type;
    m_isEnabled = data.isEnabled;
}


/**GENERIC**/
const IOComponent& IOBase::getIOComponent() const
{
    return *m_pIOComponent;
}
unsigned int IOBase::getID() const
{
    return m_pIOComponent->getID();
}
const std::string& IOBase::getName() const
{
    return m_pIOComponent->getName();
}
ClassType IOBase::getType() const
{
    return m_type;
}
const Attributes& IOBase::getButes() const
{
    return m_attributes;
}


/**IO**/
IOBaseReturn IOBase::input(IOBaseArgs)
{
    if(rCommand == "enable")
        enable();
    else if(rCommand == "disable")
        disable();
    else if(rCommand == "trigger")
        trigger();
    else
    {
        ///ERROR LOG
        std::cout << "\nCommand [" << rCommand << "] was never found.";
    }
}
void IOBase::enable()
{
    m_isEnabled = true;
    f_varEvent(m_isEnabled, Event::Enabled);
}
void IOBase::disable()
{
    m_isEnabled = false;
    f_varEvent(m_isEnabled, Event::Enabled);
}
void IOBase::trigger()
{
    f_varEvent("", Event::Triggered);
}



/**PRIVATE**/
void IOBase::f_varEvent(std::string value, Event eventType)//takes a generic variable type, and sends the data to eventer
{
    m_pIOComponent->getEventer()->event(value, eventType);
}
void IOBase::f_varEvent(int value, Event eventType)
{
    std::ostringstream convert;
    convert << value;
    m_pIOComponent->getEventer()->event(convert.str(), eventType);
}
void IOBase::f_varEvent(float value, Event eventType)
{
    std::ostringstream convert;
    convert << value;
    m_pIOComponent->getEventer()->event(convert.str(), eventType);
}
void IOBase::f_varEvent(double value, Event eventType)
{
    std::ostringstream convert;
    convert << value;
    m_pIOComponent->getEventer()->event(convert.str(), eventType);
}
