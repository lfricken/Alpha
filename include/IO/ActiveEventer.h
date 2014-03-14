#ifndef ActiveEventer_H
#define ActiveEventer_H

#include "PassiveEventer.h"
#include "IOManager.h"
#include "Courier.h"
#include "VariableNames.h"

class ActiveEventer : public PassiveEventer
{
public:
    ActiveEventer();//when we create an Active eventer, we need to pass it an io manager
    virtual ~ActiveEventer();

    int amount() const;
    void add(const Courier& courier);//gets sent a courier and puts it into its vector to be checked later

    void event(const std::string& variable, Variable variableName);

protected:
    std::vector<Courier> m_courierList;//the list of Couriers held by this eventer (each eventer is specific to a small group, or 1, variables in an entity
    static IOManager& m_rIOManager;//a reference to the world io manager
private:
};

#endif // ActiveEventer_H
