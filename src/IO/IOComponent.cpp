#include "IOComponent.hpp"

#include "defaults.hpp"
#include "globals.hpp"
#include "IOBase.hpp"
#include "IOManager.hpp"

IOComponent::IOComponent(unsigned int id, IOManager& manager)
{
    m_ID = id;
    m_name = defaults::io::name;
    m_spEventer = std::tr1::shared_ptr<ActiveEventer>(new ActiveEventer());
    m_pOwner = NULL;
}
IOComponent::~IOComponent()
{
}
void IOComponent::free()
{
    game.getGameIOManager().f_free(m_ID);
}
void IOComponent::setOwner(IOBase* pOwner)
{
    m_pOwner = pOwner;
}
IOBase* IOComponent::getOwner()
{
    return m_pOwner;
}
unsigned int IOComponent::getID() const
{
    return m_ID;
}
const std::string& IOComponent::getName() const
{
    return m_name;
}
void IOComponent::setName(const std::string& name)
{
    m_name = name;
}
ActiveEventer* IOComponent::getEventerPtr()
{
    return &*m_spEventer;
}
void IOComponent::resetEventer()
{
    m_spEventer.reset();
    m_spEventer = std::tr1::shared_ptr<ActiveEventer>(new ActiveEventer());
}
IOBaseReturn IOComponent::input(IOBaseArgs)//called for any input
{
    if(m_pOwner != NULL)
        m_pOwner->input(rInput, rCommand);
}
