#include "Camera.h"


Camera::Camera()
{
    m_zoomLevel = 1;
    m_isTracking = true;

    m_view.setViewport(sf::FloatRect(0, 0, 0.5, 1));
}
Camera::~Camera()
{

}
const sf::View& Camera::getView() const
{
    return m_view;
}
void Camera::setViewportSF(const sf::FloatRect& rPort)
{
    m_view.setViewport(rPort);
}
void Camera::setSizeSF(const sf::Vector2f& rSize)
{
    m_view.setSize(rSize);
}

void Camera::setCenter(const b2Vec2& rPos)
{
    m_view.setCenter(leon::b2Tosf<float>(rPos));
}
b2Vec2 Camera::getCenter() const
{
    leon::sfTob2(m_view.getCenter());
}


float Camera::getZoomLevel() const
{
    return m_zoomLevel;
}
void Camera::setZoomLevel(float newZoom)
{
    m_view.zoom(newZoom/m_zoomLevel);
    m_zoomLevel = newZoom;
}
void Camera::zoom(float zoomChange)
{
    m_zoomLevel *= zoomChange;
    m_view.zoom(zoomChange);
}
bool Camera::isTracking() const
{
    return m_isTracking;
}
bool Camera::toggleTracking()
{
    m_isTracking = !m_isTracking;
    if(!m_isTracking)
        m_view.setRotation(0);
    return m_isTracking;
}
