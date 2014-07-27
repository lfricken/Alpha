#ifndef AMMOCONTAINER_H
#define AMMOCONTAINER_H

class AmmoContainer
{
    public:
        AmmoContainer();
        virtual ~AmmoContainer();

        bool isReloading() const;
    protected:
    private:

    bool m_isReloading;
};

#endif // AMMOCONTAINER_H
