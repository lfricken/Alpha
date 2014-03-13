#ifndef TEXTUREALLOCATOR_H
#define TEXTUREALLOCATOR_H

#include "stdafx.h"

class TextureAllocator
{
    public:
        TextureAllocator();
        ~TextureAllocator();

        sf::Texture* request(const std::string& rFilePath);
    protected:
    private:
        std::map<std::string, std::tr1::shared_ptr<sf::Texture> > m_textures;
};

#endif // TEXTUREALLOCATOR_H
