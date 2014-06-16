#ifndef IOCOMPONENT_H
#define IOCOMPONENT_H

#include "defaults.h"
#include "Courier.h"
#include "ActiveEventer.h"

class IOComponent
{
public:
    IOComponent(unsigned int id, IOManager& manager);
    virtual ~IOComponent();

    IOBaseReturn input(IOBaseArgs);//called for any input
    void setOwner(IOBase* pOwner);

    unsigned int getID() const;
    //void setID(unsigned int id);

    const std::string& getName() const;
    void setName(const std::string& name);

    void addCouriers(const std::vector<std::tr1::shared_ptr<Courier> >& spCourierList);
    ActiveEventer* getEventer();
    void resetEventer();//used in Game::Game() to reset some pointers that otherwise get messed up

    IOManager& getIOManager();
protected:
private:
    IOManager& m_rIOManager;
    IOBase* m_pOwner;

    unsigned int m_ID;
    std::string m_name;//used by IO manager to locate specific named objects

    std::tr1::shared_ptr<ActiveEventer> m_spEventer;
};

#endif // IOCOMPONENT_H
