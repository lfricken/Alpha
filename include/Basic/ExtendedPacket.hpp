#ifndef EXTENDEDPACKET_H
#define EXTENDEDPACKET_H

#include "stdafx.hpp"

class ExtendedPacket : public sf::Packet
{
public:
    ExtendedPacket();
    ExtendedPacket(const sf::Packet& rPrimative);
    virtual ~ExtendedPacket();


    using sf::Packet::operator >>;
    using sf::Packet::operator <<;



    /**THIS ALLOWS PACKETS TO ACCEPT TUPLES**/
    template<typename ...T>
    Packet& operator >>(std::tuple<T...>& data)
    {
        if (checkSize(sizeof(data)))
        {
            data = *reinterpret_cast<const std::tuple<T...>* >(&m_data[m_readPos]);
            m_readPos += sizeof(data);
        }

        return *this;
    }
    template<typename ...T>
    Packet& operator <<(const std::tuple<T...>& data)
    {
        append(&data, sizeof(data));
        return *this;
    }


protected:
private:
};

#endif // EXTENDEDPACKET_H
