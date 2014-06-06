#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

enum Butes//used to access elements of array
{
    isSolid = 0,
};

typedef int ButeList[1];

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
    ButeList m_bute;
};

#endif // ATTRIBUTES_H
