#ifndef BINARYVECTORSEARCH_H
#define BINARYVECTORSEARCH_H

#include "stdafx.h"

template<class S, class R,typename T>
int binary_find_ptr(std::vector<S>& container, T(R::*func)() const, T id)
{
    int first = 0;
    int last = container.size()-1;
    int middle = (first+last)/2;

    while(first <= last)
    {
        if (((*container[middle]).*func)() < id)
            first = middle + 1;
        else if (((*container[middle]).*func)() == id)
            return middle;
        else
            last = middle - 1;
        middle = (first + last)/2;
    }
    if (first > last)
        return -1;
    else
    {
        ///ERROR LOG
        return -1;
    }
}

#endif //BINARYVECTORSEARCH_H
