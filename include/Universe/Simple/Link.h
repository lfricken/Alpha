#ifndef LINK_H
#define LINK_H

#include "stdafx.h"

template<class US, class THEM>
class Link
{
    friend class Link<THEM, US>;

public:
    Link(US* pUs);
    virtual ~Link();

    void link(Link<THEM, US>* pTargetLinker);
    void breakLink();//breaks the connection we have with a target

    THEM* getTargetPtr();//gives the thing we have linked to
    bool isLinked() const;

protected:
private:
    void f_inducedLink(Link<THEM, US>* pTargetLinker);//called by link function of another thing
    void f_inducedBreak();//is called by breakLink, which destroys our connection
    US* f_getPtr();//gives the thing we are linking for

    US* m_pUs;
    Link<THEM, US>* m_pTargetLinker;
};


template <class US, class THEM>
Link<US, THEM>::Link(US* pUs)
{
    m_pUs = pUs;
    m_pTargetLinker = NULL;
}
template<class US, class THEM>
Link<US, THEM>::~Link()
{
    breakLink();
}


template<class US, class THEM>
void Link<US, THEM>::link(Link<THEM, US>* pTargetLinker)
{
    breakLink();
    pTargetLinker->breakLink();
    m_pTargetLinker = pTargetLinker;
    m_pTargetLinker->f_inducedLink(this);
}
template<class US, class THEM>
void Link<US, THEM>::f_inducedLink(Link<THEM, US>* pTargetLinker)
{
    m_pTargetLinker = pTargetLinker;
}



template<class US, class THEM>
void Link<US, THEM>::breakLink()//breaks the connection we have with a target
{
    if(m_pTargetLinker != NULL)
    {
        m_pTargetLinker->f_inducedBreak();
        m_pTargetLinker = NULL;
    }
}
template<class US, class THEM>
void Link<US, THEM>::f_inducedBreak()//is called by selfInitiated break, which destroys our connection
{
    m_pTargetLinker = NULL;
}


template<class US, class THEM>
THEM* Link<US, THEM>::getTargetPtr()//gives the thing we have linked to
{
    return m_pTargetLinker->f_getPtr();
}
template<class US, class THEM>
bool  Link<US, THEM>::isLinked() const
{
    return (m_pTargetLinker != NULL);
}
template<class US, class THEM>
US* Link<US, THEM>::f_getPtr()
{
    return m_pUs;
}

#endif // LINK_H
