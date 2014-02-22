#ifndef PassiveEventer_H
#define PassiveEventer_H

#include <stdafx.h>
#include <MultipleInheritance/IOBase.h>

class PassiveEventer//look at ActiveEventer for details.
{
    public:
        PassiveEventer();
        virtual ~PassiveEventer();

        virtual void event(const std::string variable);


        virtual bool isActive() const;
    protected:
        bool m_isActive;
    private:
};

#endif // PassiveEventer_H
