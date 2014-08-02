#ifndef CAMERA_H
#define CAMERA_H

#include "stdafx.hpp"
#include "Convert.hpp"
class Camera
{
    public:
        Camera();
        virtual ~Camera();

        /**SF::VIEW**/
        const sf::View& getView() const;
        void setViewportSF(const sf::FloatRect& rPort);
        void setSizeSF(const sf::Vector2f& rSize);

        /**POSITION**/
        void setCenter(const b2Vec2& rPos);
        b2Vec2 getCenter() const;
        bool isTracking() const;
        bool toggleTracking();

        /**ROTATION**/
        void setRotation(float);//radians
        float getRotation() const;//radians
        bool rotates() const;
        bool toggleRotation();

        /**ZOOM**/
        void setZoomLevel(float newZoom);
        float getZoomLevel() const;
        void zoom(float zoomChange);//zoom by a multiple amount

    protected:
    private:
        float m_zoomLevel;///consider having max and min zoom for when we aren't tracking anything

        bool m_isTracking;//should we follow a target
        bool m_rotates;//should we spin with the target
        sf::View m_view;
};
#endif // CAMERA_H
