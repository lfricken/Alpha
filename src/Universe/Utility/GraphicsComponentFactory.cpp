#include "GraphicsComponentFactory.hpp"

GraphicsComponentFactory::GraphicsComponentFactory()
{

}
GraphicsComponentFactory::~GraphicsComponentFactory()
{

}
GraphicsComponent* GraphicsComponentFactory::generate(const GraphicsComponentData& rData)
{
    GraphicsComponentData tempData(rData);
    auto& spGfxCompList = m_layers[tempData.gfxLayer][tempData.texName];
    tempData.pParent = this;

    GraphicsComponent* ptr = new GraphicsComponent(tempData);//create the component
    spGfxCompList.push_back(std::tr1::shared_ptr<GraphicsComponent>(ptr));

    return ptr;
}
void GraphicsComponentFactory::freeComponent(GraphicsComponent* ptr)
{
    auto& spGfxCompList = m_layers[ptr->getGfxLayer()][ptr->getTexName()];

    for(auto it = spGfxCompList.begin(); it != spGfxCompList.end(); ++it)
    {
        if(ptr == &(**it))
        {
            spGfxCompList.erase(it);
            break;
        }
    }
}
void GraphicsComponentFactory::draw(sf::RenderWindow& rWindow)
{
    /**1 loop over the layers**/
    /**2 loop over the sprite groups**/
    /**3 loop over elements in sprite groups**/
    /**4 draw those elements**/
    for(auto it_layer = m_layers.begin(); it_layer != m_layers.end(); ++it_layer)//1
        for(auto it_gfxCompGroup = it_layer->second.begin(); it_gfxCompGroup != it_layer->second.end(); ++it_gfxCompGroup)//2
            for(auto it_comp = it_gfxCompGroup->second.begin(); it_comp != it_gfxCompGroup->second.end(); ++it_comp)//3
            {
                (**it_comp).update();
                rWindow.draw( (**it_comp).getSprite() );//4
            }
}
