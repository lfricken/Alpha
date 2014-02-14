#ifndef BOX_H
#define BOX_H

#include <graphics.h>
#include <stdafx.h>

class Box : public graphics
{
    public:
        Box();
        Box(float radius, b2Vec2 position, b2World& world, unsigned const int scale);
        virtual ~Box();

        void draw(sf::RenderWindow& window);
    protected:
    private:
        sf::RectangleShape myShape;
        unsigned int theScale;
        b2Body* myPhys;
};

#endif // BOX_H
