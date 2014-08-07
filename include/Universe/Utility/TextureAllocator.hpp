#ifndef TEXTUREALLOCATOR_H
#define TEXTUREALLOCATOR_H

#include "stdafx.hpp"
#include "defaults.hpp"

class TextureAllocator
{
    public:
        TextureAllocator(bool shouldSmoothTextures);
        ~TextureAllocator();

        void smoothTextures(bool smooth);//loops through our textures and either smooths them or not, and sets m_smoothTextures apropriatly
        sf::Texture* request(const std::string& rFilePath);
    protected:
    private:
        bool m_smoothTextures;
        std::map<std::string, std::tr1::shared_ptr<sf::Texture> > m_textures;
};

#endif // TEXTUREALLOCATOR_H
