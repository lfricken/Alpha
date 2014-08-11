#include "ZoomModComponent.hpp"

ZoomModComponent::ZoomModComponent(T_Zoom contribution)
{
    zoomMultiple = contribution;
    hasContributed = false;
}
ZoomModComponent::~ZoomModComponent()
{

}
void ZoomModComponent::give(ZoomPool& rPool)
{
    if(hasContributed == false)
    {
        hasContributed = true;
        rPool.changeMult(zoomMultiple);
    }
}
void ZoomModComponent::take(ZoomPool& rPool)
{
    if(hasContributed == true)
    {
        hasContributed = false;
        rPool.changeMult(1/zoomMultiple);
    }
}
