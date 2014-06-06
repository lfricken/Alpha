#include "IOBase.h"
#include "globals.h"

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
    m_name = data.name;
    m_type = data.type;
    m_isEnabled = data.isEnabled;
    m_ID = Enumerate(m_name);
    addCouriers(data.spCourierList);
}
void IOBase::resetEventer()///wtf is this for?
{
    m_spEventer.reset();
    m_spEventer = std::tr1::shared_ptr<ActiveEventer>(new ActiveEventer());
}
void IOBase::addCouriers(const std::vector<std::tr1::shared_ptr<Courier> >& spCourierList)
{
    if(!m_spEventer)//if we don't have an active eventer(because that would mean m_spEventer returns false)
        m_spEventer = std::tr1::shared_ptr<ActiveEventer>(new ActiveEventer());

    for(std::vector<std::tr1::shared_ptr<Courier> >::const_iterator it = spCourierList.begin(); it != spCourierList.end(); ++it)
        m_spEventer->add(*it);
}
std::tr1::shared_ptr<ActiveEventer> IOBase::getEventer()
{
    return m_spEventer;
}
IOManager& IOBase::getIOManager()
{
    return m_rIOManager;
}
void IOBase::setName(const std::string& name)//finished
{
    m_name = name;
}
const std::string& IOBase::getName() const//finished
{
    return m_name;
}
unsigned long long int IOBase::getID() const
{
    return m_ID;
}
ClassType IOBase::getType() const
{
    return m_type;
}
const Attributes& IOBase::getButes() const
{
    return m_attributes;
}
/**
int IOBase::damage(int damage)
{
    return 1;
}

int IOBase::getHealth() const
{
    return 1;
}**/
IOBaseReturn IOBase::input_1(IOBaseArgs) {}
IOBaseReturn IOBase::input_2(IOBaseArgs) {}
IOBaseReturn IOBase::input_3(IOBaseArgs) {}
IOBaseReturn IOBase::input_4(IOBaseArgs) {}
IOBaseReturn IOBase::input_5(IOBaseArgs) {}
IOBaseReturn IOBase::input_6(IOBaseArgs) {}
IOBaseReturn IOBase::input_7(IOBaseArgs) {}
IOBaseReturn IOBase::input_8(IOBaseArgs) {}
IOBaseReturn IOBase::input_9(IOBaseArgs) {}
IOBaseReturn IOBase::input_10(IOBaseArgs) {}
IOBaseReturn IOBase::input_11(IOBaseArgs) {}
IOBaseReturn IOBase::input_12(IOBaseArgs) {}
IOBaseReturn IOBase::input_13(IOBaseArgs) {}
IOBaseReturn IOBase::input_14(IOBaseArgs) {}
IOBaseReturn IOBase::input_15(IOBaseArgs) {}
IOBaseReturn IOBase::input_16(IOBaseArgs) {}
IOBaseReturn IOBase::input_17(IOBaseArgs) {}
IOBaseReturn IOBase::input_18(IOBaseArgs) {}
IOBaseReturn IOBase::input_19(IOBaseArgs) {}
IOBaseReturn IOBase::input_20(IOBaseArgs) {}
