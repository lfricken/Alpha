#include "GraphicsComponentFactory.hpp"

GraphicsComponentFactory::GraphicsComponentFactory()
{

}
GraphicsComponentFactory::~GraphicsComponentFactory()
{

}
BaseGraphicsComponent* GraphicsComponentFactory::generate(const BaseGraphicsComponentData& rData)
{
    auto& spGfxCompList = m_layers[rData.gfxLayer][rData.texName];

    BaseGraphicsComponent* ptr = rData.generate(this);//create the component
    spGfxCompList.push_back(std::tr1::shared_ptr<BaseGraphicsComponent>(ptr));

    return ptr;
}
void GraphicsComponentFactory::freeComponent(BaseGraphicsComponent* ptr)
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
                (**it_comp).draw(rWindow);//4
            }
}
