#include "Camera.hpp"


Camera::Camera()
{
    m_zoomLevel = 1;
    m_isTracking = true;
    m_rotates = true;

    m_view.setViewport(sf::FloatRect(0, 0, 0.5, 1));
}
Camera::~Camera()
{

}


/**SF::VIEW**/
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




/**POSITION**/
void Camera::setCenter(const b2Vec2& rPos)
{
    m_view.setCenter(leon::b2Tosf<float>(rPos));
}
b2Vec2 Camera::getCenter() const
{
    leon::sfTob2(m_view.getCenter());
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




/**ROTATION**/
void Camera::setRotation(float r)
{
    m_view.setRotation(-leon::radToDeg(r));
}
float Camera::getRotation() const
{
    return -leon::degToRad(m_view.getRotation());
}
bool Camera::rotates() const
{
    return m_rotates;
}
bool Camera::toggleRotation()
{
    m_rotates = !m_rotates;
    return m_rotates;
}


/**ZOOM**/
void Camera::setZoomLevel(float newZoom)
{
    m_view.zoom(newZoom/m_zoomLevel);
    m_zoomLevel = newZoom;
}
float Camera::getZoomLevel() const
{
    return m_zoomLevel;
}
void Camera::zoom(float zoomChange)
{
    m_zoomLevel *= zoomChange;
    m_view.zoom(zoomChange);
}
