#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdafx.h>

class graphics
{
    public:
        graphics();
        virtual ~graphics();

        void virtual draw(sf::RenderWindow& window);
    protected:
        b2Vec2 my_gfx_position;
    private:
};

#endif // GRAPHICS_H
