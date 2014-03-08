#include "Camera.h"

Camera::Camera()
{
    m_zoomLevel = 1;
}
Camera::~Camera()
{

}
sf::View& Camera::getView()
{
    return m_view;
}
const float& Camera::getZoomLevel()
{
    return m_zoomLevel;
}
void Camera::setZoomLevel(float newZoom)
{
    m_zoomLevel = newZoom;
}
void Camera::zoomFactor(float zoomChange)
{
    m_zoomLevel *= zoomChange;
}
bool Camera::isTracking()
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
