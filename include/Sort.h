#ifndef SORT_H
#define SORT_H

template<class S, class R,typename T>
inline void SortPtrVector(std::vector<S>& container, T(R::*compareFunc)() const)
{
    std::vector<S> temp = container;
    typename std::vector<S>::iterator current;
    container.clear();

    /**SORT FROM LOWEST TO HIGHEST**/
    while(!temp.empty())
    {
        /**find the lowest valued item**/
        current = temp.begin();
        for(typename std::vector<S>::iterator it = temp.begin(); it != temp.end(); ++it)
        {
            if(  ((**it).*compareFunc)()  <  ((**current).*compareFunc)()  )/**was lower than our current value**/
            {
                current = it;
            }
        }
        container.push_back(*current);
        temp.erase(current);
    }
}

template<class S, class R,typename T>
inline void InsertPtrVector(std::vector<S>& container, T(R::*compareFunc)() const, const S& newElement)
{
    typename std::vector<S>::iterator it;
    for(it = container.begin(); it != container.end(); ++it)
    {
        if( ((**it).*compareFunc)() >= ((*newElement).*compareFunc)() )
            break;
    }
    container.insert(it, newElement);
}

template<class S, class R,typename T>
inline int BinarySearchPtrVector(std::vector<S>& container, T(R::*func)() const, T id)
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

#endif // SORT_H
