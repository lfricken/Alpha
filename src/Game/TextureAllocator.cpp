#include "TextureAllocator.h"

using namespace std;
using namespace sf;

TextureAllocator::TextureAllocator(bool shouldSmoothTextures)
{
    m_smoothTextures = shouldSmoothTextures;

    tr1::shared_ptr<Texture> spTempTex(new Texture);
    if(!spTempTex->loadFromFile(def::gfx::texName))/**cant be loaded**/
    {
        ///ERROR LOG
        cout << "\nThere was an error loading the texture [" << def::gfx::texName << "].";
    }
    spTempTex->setSmooth(m_smoothTextures);
    m_textures[def::gfx::texName] = spTempTex;
}
TextureAllocator::~TextureAllocator()
{

}
Texture* TextureAllocator::request(const std::string& rFilePath)
{
    map<string, tr1::shared_ptr<Texture> >::iterator it = m_textures.find(rFilePath);

    if(it != m_textures.end())/**we already have it**/
        return &(*(it->second));
    else/**we dont have it loaded**/
    {
        tr1::shared_ptr<Texture> spTempTex(new Texture);
        if(!spTempTex->loadFromFile(rFilePath))/**cant be loaded**/
        {
            ///ERROR LOG
            cout << "\nThere was an error loading the texture [" << rFilePath << "].";
            return &*m_textures[def::gfx::texName];
        }
        m_textures[rFilePath] = spTempTex;
        spTempTex->setSmooth(m_smoothTextures);
        return &*spTempTex;
    }
}
