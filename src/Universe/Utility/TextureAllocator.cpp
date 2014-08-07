#include "TextureAllocator.hpp"

using namespace std;
using namespace sf;

TextureAllocator::TextureAllocator(bool shouldSmoothTextures)
{
    m_smoothTextures = shouldSmoothTextures;

    tr1::shared_ptr<Texture> spTempTex(new Texture);
    if(!spTempTex->loadFromFile(defaults::graphics::texName))/**cant be loaded**/
    {
        ///ERROR LOG
        cout << "\nThere was an error loading the texture [" << defaults::graphics::texName << "].";
    }
    spTempTex->setSmooth(m_smoothTextures);
    m_textures[defaults::graphics::texName] = spTempTex;
}
TextureAllocator::~TextureAllocator()
{

}
void TextureAllocator::smoothTextures(bool smooth)
{
    m_smoothTextures = smooth;
    for(auto it = m_textures.begin(); it != m_textures.end(); ++it)//loop through all our textures to make them smooth
        it->second->setSmooth(m_smoothTextures);
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
            return &*m_textures[defaults::graphics::texName];
        }
        m_textures[rFilePath] = spTempTex;
        spTempTex->setSmooth(m_smoothTextures);
        return &*spTempTex;
    }
}
