#include "IOBase.h"
#include "globals.h"

using namespace std;

IOManager& IOBase::m_rIOManager = game.getGameIOManager();

IOBase::IOBase()//unfinished
{
}
IOBase::IOBase(const IOBaseData& data)
{
    m_name = data.name;
    m_type = data.type;
}
IOBase::~IOBase()//unfinished
{
}
IOManager& IOBase::getIOManager()
{
    return m_rIOManager;
}
void IOBase::setName(const string& name)//finished
{
    m_name = name;
}
const string& IOBase::getName() const//finished
{
    return m_name;
}
unsigned int IOBase::getID() const
{
    return m_ID;
}
void IOBase::damage(int damage)
{
}
void IOBase::input_1(const std::string& rInput) {}
void IOBase::input_2(const std::string& rInput) {}
void IOBase::input_3(const std::string& rInput) {}
void IOBase::input_4(const std::string& rInput) {}
void IOBase::input_5(const std::string& rInput) {}
void IOBase::input_6(const std::string& rInput) {}
void IOBase::input_7(const std::string& rInput) {}
void IOBase::input_8(const std::string& rInput) {}
void IOBase::input_9(const std::string& rInput) {}
void IOBase::input_10(const std::string& rInput) {}
