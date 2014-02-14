

#include <Universe/MultiTileMap.h>
///We need to take into account the display priority of an entity.
///Then we add that item to the list last, so it gets displayed last(on top)
///Look at graphicsBase.
/**
1. Make count of how many of each texture type there is.
2. Take the total count and resize m_arrays.
3. Go through m_arrays and resize each VertexArray, and set their pTexture;
4. Go through the DGModule list, find their texturedVertex element,
set their vertex pointer using nextAccessed and update nextAccessed;
**/
///work through and verify all this code
///CAN WE PASS A GENERIC GRAPHICS BASE VECTOR, CAUSE THAT WOULD BE NICE!
void MultiTileMap::add(std::vector<std::tr1::shared_ptr<DGModule> >& rDGModuleSPList)
{
    typedef std::vector<std::tr1::shared_ptr<DGModule> >::const_iterator vec_spDGModule_it;
    typedef std::vector<std::tr1::shared_ptr<texturedVertices> >::iterator vec_spTexVert_it;

    /**1**/
    std::map<std::string, int> texTally;
    for(vec_spDGModule_it it = rDGModuleSPList.begin(); it != rDGModuleSPList.end(); ++it)
    {
        texTally[(*it)->getTexName()] += 1;
    }

    /**2**/
    m_TexVertSPList.resize(texTally.size());


    /**3**////STILL HAVE TO SET THE pTexture!!!!!
    sf::Texture* genericTex = new sf::Texture;///TEMPORARY, REMOVE ME ASAP
    genericTex->loadFromFile("tileset.png");///TEMPORARY, REMOVE ME ASAP

    vec_spTexVert_it it_texVert = m_TexVertSPList.begin();
    for(std::map<std::string, int>::const_iterator it_map = texTally.begin(); it_map != texTally.end(); ++it_map, ++it_texVert)
    {
        (*it_texVert) = std::tr1::shared_ptr<texturedVertices>(new texturedVertices);
        (*it_texVert)->pTexture = genericTex;///request "textureName" from texManager
        (*it_texVert)->textureName = it_map->first;
        (*it_texVert)->vertices.setPrimitiveType(sf::Quads);
        (*it_texVert)->vertices.resize(it_map->second*4);//*4 because each one has 4 vertices(quad)
        (*it_texVert)->nextAccessed = 0;
    }


    /**4**/
    for(vec_spDGModule_it it_DGModule = rDGModuleSPList.begin(); it_DGModule != rDGModuleSPList.end(); ++it_DGModule)
    {
        for(it_texVert = m_TexVertSPList.begin(); it_texVert != m_TexVertSPList.end(); ++it_texVert)
        {
            if( (*it_texVert)->textureName == (*it_DGModule)->getTexName() )
            {
                (*it_DGModule)->setVertex( &(*it_texVert)->vertices[ (*it_texVert)->nextAccessed ] );//GraphicsBase::setVertex should handle all this
                (*it_texVert)->nextAccessed += 4;
            }
        }
    }
}
void MultiTileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    for(std::vector<std::tr1::shared_ptr<texturedVertices> >::const_iterator it_texVert = m_TexVertSPList.begin(); it_texVert != m_TexVertSPList.end(); ++it_texVert)
    {
        states.texture = (*it_texVert)->pTexture;
        target.draw((*it_texVert)->vertices, states);
    }
}
