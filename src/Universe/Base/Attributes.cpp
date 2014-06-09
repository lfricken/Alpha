#include "Attributes.h"


Attributes::Attributes()
{
    for(unsigned int i = 0; i < Butes::NUMBER_OF_ATTRIBUTES; ++i)
        m_buteList[i] = -1;
}
Attributes::~Attributes()
{

}


void Attributes::setBute(Butes index, int val)
{
    m_buteList[index] = val;
}
int Attributes::getBute(Butes index) const
{
    return m_buteList[index];
}
