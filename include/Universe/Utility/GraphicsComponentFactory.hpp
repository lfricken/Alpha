#ifndef GRAPHICSCOMPONENTFACTORY_H
#define GRAPHICSCOMPONENTFACTORY_H

#include "stdafx.hpp"
#include "GraphicsLayer.hpp"
#include "GraphicsComponent.hpp"

/**A map of textureNames, which are associated with a vector of components**/



class GraphicsComponentFactory
{
public:
    GraphicsComponentFactory();
    virtual ~GraphicsComponentFactory();

    GraphicsComponent* generate(const GraphicsComponentData& rData);
    void freeComponent(GraphicsComponent* ptr);

    void draw(sf::RenderWindow& rWindow);//draw all of the graphics components we hold

protected:
private:
    typedef std::vector<std::tr1::shared_ptr<GraphicsComponent> > gfxCompGroup;
    typedef std::map<std::string, gfxCompGroup> Layer;
    std::map<GraphicsLayer, Layer> m_layers;/**A map of GraphicsLayers that correspond to some Layer**/
};

#endif // GRAPHICSCOMPONENTFACTORY_H
