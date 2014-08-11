#ifndef ZOOMMODCOMPONENT_H
#define ZOOMMODCOMPONENT_H

#include "VariableNames.hpp"

class ZoomModComponent
{
public:
    ZoomModComponent(T_Zoom zoomMult);
    virtual ~ZoomModComponent();

    void give(ZoomPool& rPool);
    void take(ZoomPool& rPool);
protected:
private:
    bool hasContributed;
    T_Zoom zoomMultiple;
};

#endif // ZOOMMODCOMPONENT_H
