#include "Attributes.h"


Attributes::Attributes()
{
    m_bute[Butes::isSolid] = false;





}
Attributes::Attributes(int a)
{
    m_bute[Butes::isSolid] = a;








}
Attributes::~Attributes()
{

}


void Attributes::setBute(Butes index, int val)
{
    m_bute[index] = val;
}
int Attributes::getBute(Butes index) const
{
    return m_bute[index];
}
