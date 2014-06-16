#ifndef IOMANAGER_H
#define IOMANAGER_H

#include "stdafx.h"
#include "Package.h"
#include "IOComponent.h"

class IOManager
{
    public:
        IOManager();
        ~IOManager();

        void recieve(Package& rPackage);//finished//called by a class to give the package to us
        void update(float timeChange);//iterate over the list of Packages, and if the time is up, call universe.send(Package); on that package

        IOComponent* createIOComponent(const std::string& name);//finds an empty IOComponent, adds it's name and ID to the name-ID map, and returns a pointer to it
        void setTargets();//goes through each package in each courier in each IOComponent and uses a map to get the right target ID.

    protected:
    private:
        IOComponent* m_currentTarget;
        std::vector<Packagelet> m_packageletList;//list of packages to be sent

        std::vector<unsigned int> m_IOCFreeList;//holds free elements of m_IOComponentList
        std::vector<std::tr1::shared_ptr<IOComponent> > m_IOComponentList;//list of all IOComponents

};

#endif // IOMANAGER_H
