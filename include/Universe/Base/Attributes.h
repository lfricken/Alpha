#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

enum Butes//used to access elements of array
{
    isSolid = 0,//used for array indexes, they automatically start counting up
    isDestructable,

    NUMBER_OF_ATTRIBUTES,
};

typedef int ButeList[NUMBER_OF_ATTRIBUTES];

class Attributes/**Bute stands for Attribute**/
{
public:
    Attributes();
    Attributes(int a);
    virtual ~Attributes();

    void setBute(Butes index, int val);
    int getBute(Butes index) const;


protected:
private:
    ButeList m_buteList;
};

#endif // ATTRIBUTES_H
