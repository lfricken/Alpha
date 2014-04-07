#ifndef ENUMERATE_H
#define ENUMERATE_H

/**inline because otherwise we get multiple defs compile error**/
inline unsigned long long int Enumerate(const std::string& input)
{
    unsigned long long int result = 0;
    unsigned char current;
    int maxIndex = input.length()-1;
    int maxChars = 10;
    int data = 0;

    for(int i = maxIndex, c = 1; (i>=0) && (c <= maxChars); --i, ++c)
    {
        current = input[i];
        if(current < 48)/**space**/
            data = (current-32+62);
        else if(current < 65)/**numbers**/
            data = static_cast<int>(current-48+0);
        else if(current < 95)/**uppercase**/
            data = static_cast<int>(current-65+10);
        else if(current == 95)/**underscore**/
            data = static_cast<int>(current-95+63);
        else if(current > 95)/**lowercase**/
            data = static_cast<int>(current-97+36);
        else
            data = 0;

        result |= (data << (c-1)*6);
    }
    return result;
}

#endif // ENUMERATE_H
