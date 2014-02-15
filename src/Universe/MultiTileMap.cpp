

#include <Universe/MultiTileMap.h>
using namespace std;


MultiTileMap::MultiTileMap(const MultiTileMap& old)
{
    cout << "\nTileMap Copy Called...";
    m_tileSize = old.getTileSize();
    m_TexVertSPList = old.getTexVertList();
    setOrigin(old.getOrigin());
    cout << "Completed.";
}
MultiTileMap& MultiTileMap::operator= (const MultiTileMap& other)
{
    if (this != &other)// protect against invalid self-assignment
    {
        m_tileSize = other.getTileSize();
        m_TexVertSPList = other.getTexVertList();
        setOrigin(other.getOrigin());
    }
    return *this;
}
MultiTileMap::~MultiTileMap() {};

///We need to take into account the display priority of an entity.
///Then we add that item to the list last, so it gets displayed last(on top)
///Look at graphicsBase.
/**
1. Make count of how many of each texture type there is.
2. Take the total count and resize m_arrays.
3. Go through m_arrays and resize each VertexArray, and set their pTexture;
4. Go through the gfxBase list, find each gfxBase  element in m_TexVertSPList,
set their vertex pointer using nextAccessed and update nextAccessed;
**/
///work through and verify all this code
void MultiTileMap::add(vector<GraphicsBase*> gfxBaseList)
{
    /**1**/
    map<string, int> texTally;
    for(vector<GraphicsBase*>::const_iterator it = gfxBaseList.begin(); it != gfxBaseList.end(); ++it)
    {
        texTally[(*it)->getTexName()] += 1;
    }


    /**2**/
    m_TexVertSPList.resize(texTally.size());


    /**3**////STILL HAVE TO SET THE pTexture!!!!!
    sf::Texture* genericTex = new sf::Texture;///TEMPORARY, REMOVE ME ASAP
    genericTex->loadFromFile("textures/tileset.png");///TEMPORARY, REMOVE ME ASAP


    vector<tr1::shared_ptr<texturedVertices> >::iterator it_texVert = m_TexVertSPList.begin();
    for(map<string, int>::const_iterator it_map = texTally.begin(); it_map != texTally.end(); ++it_map, ++it_texVert)
    {
        (*it_texVert) = tr1::shared_ptr<texturedVertices>(new texturedVertices);
        (*it_texVert)->pTexture = genericTex;///request "textureName" from texManager
        (*it_texVert)->textureName = it_map->first;//go through our map of textures to find the correct one to associate with this
        (*it_texVert)->vertices.setPrimitiveType(sf::Quads);//these are squares that we want to hold
        (*it_texVert)->vertices.resize(it_map->second*4);//*4 because each one has 4 vertices/(quad)
        (*it_texVert)->nextAccessed = 0;//for use later
    }


    /**4**/
    for(vector<GraphicsBase*>::iterator it_gfxBase = gfxBaseList.begin(); it_gfxBase != gfxBaseList.end(); ++it_gfxBase)
    {
        for(it_texVert = m_TexVertSPList.begin(); it_texVert != m_TexVertSPList.end(); ++it_texVert)
        {
            if( (*it_texVert)->textureName == (*it_gfxBase)->getTexName() )
            {
                (*it_gfxBase)->setVertex( &(*it_texVert)->vertices[ (*it_texVert)->nextAccessed ] );//GraphicsBase::setVertex should handle all this???
                (*it_texVert)->nextAccessed += 4;
            }
        }
    }
}
void MultiTileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    for(vector<tr1::shared_ptr<texturedVertices> >::const_iterator it_texVert = m_TexVertSPList.begin(); it_texVert != m_TexVertSPList.end(); ++it_texVert)
    {
        states.texture = (*it_texVert)->pTexture;
        target.draw((*it_texVert)->vertices, states);
    }
}

const sf::Vector2i& MultiTileMap::getTileSize() const
{
    return m_tileSize;
}
const vector<tr1::shared_ptr<texturedVertices> >& MultiTileMap::getTexVertList() const
{
    return m_TexVertSPList;
}
