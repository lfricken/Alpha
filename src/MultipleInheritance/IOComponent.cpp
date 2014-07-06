#include "IOComponent.h"

#include "defaults.h"
#include "IOBase.h"
#include "IOManager.h"

IOComponent::IOComponent(unsigned int id, IOManager& manager) : m_rIOManager(manager)
{
    m_ID = id;
    m_name = def::io::name;
    m_spEventer = std::tr1::shared_ptr<ActiveEventer>(new ActiveEventer());
    m_pOwner = NULL;
}
IOComponent::~IOComponent()
{
}
void IOComponent::free()
{
    m_rIOManager.f_free(m_ID);
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
void IOComponent::addCouriers(const std::vector<std::tr1::shared_ptr<Courier> >& spCourierList)
{
    if(!m_spEventer)//if we don't have an active eventer(because that would mean m_spEventer returns false)
        m_spEventer = std::tr1::shared_ptr<ActiveEventer>(new ActiveEventer());

    for(std::vector<std::tr1::shared_ptr<Courier> >::const_iterator it = spCourierList.begin(); it != spCourierList.end(); ++it)
        m_spEventer->add(*it);
}
ActiveEventer* IOComponent::getEventer()
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
