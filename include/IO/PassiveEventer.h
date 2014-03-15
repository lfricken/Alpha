#ifndef PassiveEventer_H
#define PassiveEventer_H

#include "Courier.h"

class PassiveEventer//look at ActiveEventer for details.
{
public:
    PassiveEventer();
    virtual ~PassiveEventer();

    virtual int amount() const;
    virtual void add(std::tr1::shared_ptr<Courier> spCourier);//gets sent a courier and puts it into its vector to be checked later
    virtual void event(const std::string& variable, Variable variableName);

protected:
private:
};

#endif // PassiveEventer_H
