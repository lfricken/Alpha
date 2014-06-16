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
IOBase::~IOBase()//unfinished
{
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
/*IOManager& IOBase::getIOManager()
{
    return m_rIOManager;
}*/

ClassType IOBase::getType() const
{
    return m_type;
}
const Attributes& IOBase::getButes() const
{
    return m_attributes;
}


IOBaseReturn IOBase::input(IOBaseArgs)
{

}
void IOBase::enable()
{

}
void IOBase::disable()
{

}


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
