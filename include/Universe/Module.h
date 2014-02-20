#ifndef DMODULE_H
#define DMODULE_H

#include <MultipleInheritance/IOBase.h>
#include <MultipleInheritance/PhysicsBase.h>

class Module : public IOBase, public PhysicsBase
{
    public:
        /** Default constructor */
        Module();
        /** Default destructor */
        virtual ~Module();
    protected:
    private:
};

#endif // DMODULE_H
