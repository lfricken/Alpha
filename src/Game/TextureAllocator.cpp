#include "TextureAllocator.h"

using namespace std;
using namespace sf;

TextureAllocator::TextureAllocator()
{
    tr1::shared_ptr<Texture> spTempTex(new Texture);
    if(!spTempTex->loadFromFile(defaultTexName))/**cant be loaded**/
    {
        ///ERROR LOG
        cout << "\nThere was an error loading the texture [" << defaultTexName << "].";
    }
    m_textures[defaultTexName] = spTempTex;
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
            return &*m_textures[defaultTexName];
        }
        m_textures[rFilePath] = spTempTex;
        return &*spTempTex;
    }
}
