#include "TextureAllocator.h"

using namespace std;
using namespace sf;

TextureAllocator::TextureAllocator()
{

}

TextureAllocator::~TextureAllocator()
{

}
Texture* TextureAllocator::request(const std::string& rFilePath)
{
    map<string, tr1::shared_ptr<Texture> >::iterator it = m_textures.find(rFilePath);

    if(it != m_textures.end())
        return &(*(it->second));
    else
    {
        Texture* pTempTex = new Texture;
        if(!pTempTex->loadFromFile(rFilePath))
        {
            cout << "\nThere was an error loading the texture [" << rFilePath << "]";
            ///ERROR LOG
            return NULL;
        }
        m_textures[rFilePath] = tr1::shared_ptr<Texture>(pTempTex);
        return pTempTex;
    }
}
