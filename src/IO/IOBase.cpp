#include "IOBase.hpp"
#include "globals.hpp"
#include "IOManager.hpp"

using namespace std;

IOBase::IOBase()
{
    IOBaseData data;
    f_initialize(data);
}
IOBase::IOBase(const IOBaseData& rData)
{
    f_initialize(rData);
}
IOBase::~IOBase()
{
    m_pIOComponent->free();
}
void IOBase::f_initialize(const IOBaseData& rData)
{
    m_pIOComponent = game.getGameIOManager().createIOComponent(rData.name);
    m_pIOComponent->setOwner(this);
    m_pIOComponent->getEventerPtr()->addList(rData.courierList);

    m_attributes = rData.butes;

    m_type = rData.type;

    m_isEnabled = rData.isEnabled;

    if(rData.isEnabled)
        enable();//DOES NOT CALL DERIVED BECAUSE THE DERIVED PART OF THE CLASS HAS NOT BEEN GENERATED yet
    else
        disable();
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
    (void)rInput;//shutup the compiler about unused
    if(rCommand == "enable")
        enable();
    else if(rCommand == "disable")
        disable();
    else if(rCommand == "trigger")
        trigger();
    else
    {
        ///ERROR LOG
        std::cout << "\nCommand [" << rCommand << "] was never found in object [" << m_pIOComponent->getName() << "].";
    }
}
void IOBase::enable()
{
        ///if(m_stateGraph.cando this)
    m_isEnabled = true;
    enablePostHook();
    f_varEvent(m_isEnabled, Event::Enabled);
}
void IOBase::enablePostHook()
{

}
void IOBase::disable()
{
        ///if(m_stateGraph.cando this)
    m_isEnabled = false;
    disablePostHook();
    f_varEvent(m_isEnabled, Event::Enabled);
}
void IOBase::disablePostHook()
{

}
void IOBase::trigger()
{
    f_varEvent("", Event::Triggered);
}



/**PRIVATE**/
void IOBase::f_varEvent(std::string value, Event eventType)//takes a generic variable type, and sends the data to eventer
{
    m_pIOComponent->getEventerPtr()->event(value, eventType);
}
void IOBase::f_varEvent(int value, Event eventType)
{
    std::ostringstream convert;
    convert << value;
    m_pIOComponent->getEventerPtr()->event(convert.str(), eventType);
}
void IOBase::f_varEvent(float value, Event eventType)
{
    std::ostringstream convert;
    convert << value;
    m_pIOComponent->getEventerPtr()->event(convert.str(), eventType);
}
void IOBase::f_varEvent(double value, Event eventType)
{
    std::ostringstream convert;
    convert << value;
    m_pIOComponent->getEventerPtr()->event(convert.str(), eventType);
}
