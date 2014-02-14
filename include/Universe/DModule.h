#ifndef DMODULE_H
#define DMODULE_H

#include <MultipleInheritance/IOBase.h>
#include <MultipleInheritance/PhysicsBase.h>

class DModule : public IOBase, public PhysicsBase
{
    public:
        /** Default constructor */
        DModule();
        /** Default destructor */
        virtual ~DModule();
    protected:
    private:
};

#endif // DMODULE_H
