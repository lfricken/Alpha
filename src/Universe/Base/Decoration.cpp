#include "Decoration.h"

Decoration::Decoration() : m_gfxComp()
{
    DecorationData data;
    f_init(data);
}
Decoration::Decoration(const DecorationData& rData) : m_gfxComp(rData.gfxCompData)
{
    f_init(rData);
}
Decoration::~Decoration()
{

}
void Decoration::f_init(const DecorationData& rData)
{

}
