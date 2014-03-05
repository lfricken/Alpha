#include "DebugDraw.h"

#include <globals.h>
sf::RenderWindow& DebugDraw::m_rWindow = game.getGameWindow();

DebugDraw::DebugDraw()
{
    //ctor
}

DebugDraw::~DebugDraw()
{

}
void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{

}
void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    m_convex;
    m_convex.setPointCount(vertexCount);
    m_convex.setFillColor(sf::Color(0,48,0,255));
    m_convex.setOutlineColor(sf::Color(0,100,0,255));
    m_convex.setOutlineThickness(-1);

    for (int i = 0; i < vertexCount; i++)
    {
        m_convex.setPoint(i, sf::Vector2f(vertices[i].x*scale, vertices[i].y*scale));
    }
    m_rWindow.draw(m_convex);
}
void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{

}
void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{

}
void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{

}
void DebugDraw::DrawTransform(const b2Transform& xf)
{

}
void SetWindow(const sf::RenderWindow& rWindow)
{

}
