#include "IOBase.h"
#include "globals.h"


IOManager& IOBase::m_rIOManager = game.getGameIOManager();

IOBase::IOBase()//unfinished
{
    IOBaseData data;
    data.name = "unknown name";
    data.type = "unknown type";
    initialize(data);
}
IOBase::IOBase(const IOBaseData& data)
{
    initialize(data);
}
IOBase::~IOBase()//unfinished
{
}
void IOBase::initialize(const IOBaseData& data)
{
    m_name = data.name;
    m_type = data.type;
    addCouriers(data.spCourierList);
}
void IOBase::addCouriers(const std::vector<std::tr1::shared_ptr<Courier> >& spCourierList)
{
    if(!m_spEventer)
        m_spEventer = std::tr1::shared_ptr<PassiveEventer>(new PassiveEventer());

    if(m_spEventer->amount() == 0 && spCourierList.size() == 0)//if we had a passive eventer before
    {
        m_spEventer.reset();
        m_spEventer = std::tr1::shared_ptr<PassiveEventer>(new PassiveEventer());
    }
    else if(m_spEventer->amount() != 0 && spCourierList.size() != 0)
    {
        for(std::vector<std::tr1::shared_ptr<Courier> >::const_iterator it = spCourierList.begin(); it != spCourierList.end(); ++it)
            m_spEventer->add(*it);
    }
    else if(m_spEventer->amount() == 0 && spCourierList.size() != 0)
    {
        m_spEventer.reset();
        m_spEventer = std::tr1::shared_ptr<PassiveEventer>(new ActiveEventer());
        for(std::vector<std::tr1::shared_ptr<Courier> >::const_iterator it = spCourierList.begin(); it != spCourierList.end(); ++it)
            m_spEventer->add(*it);
    }
    else if(m_spEventer->amount() != 0 && spCourierList.size() == 0)
    {
        //DO NOTHING
    }
}
std::tr1::shared_ptr<PassiveEventer> IOBase::getEventer()
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
unsigned int IOBase::getID() const
{
    return m_ID;
}
void IOBase::f_setID(unsigned int newID)
{
    m_ID = newID;
}
int IOBase::damage(int damage)
{
    return 1;
}
int IOBase::getHealth() const
{
    return 1;
}
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
