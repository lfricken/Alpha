#ifndef ART_H
#define ART_H

#include <stdafx.h>
///wip

class Art
{
    public:
        Art();
        Art(b2Vec2 position);
        virtual ~Art();

        void draw(sf::RenderWindow& window);
    protected:
    private:
        b2Vec2 position;
};

#endif // ART_H
