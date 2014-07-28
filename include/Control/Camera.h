#ifndef CAMERA_H
#define CAMERA_H

#include "stdafx.h"
#include "Angles.h"
class Camera
{
    public:
        Camera();
        virtual ~Camera();

        const sf::View& getView() const;
        void setViewportSF(const sf::FloatRect& rPort);
        void setSizeSF(const sf::Vector2f& rSize);

        void setCenter(const b2Vec2& rPos);
        b2Vec2 getCenter() const;

        void setZoomLevel(float newZoom);
        float getZoomLevel() const;
        void zoom(float zoomChange);//zoom by a multiple amount

        bool isTracking() const;
        bool toggleTracking();
    protected:
    private:
        bool m_isTracking;
        float m_zoomLevel;
        ///enum mode (like 1,2,3, or 4 players)
        ///and which one are we?
        sf::View m_view;
};
#endif // CAMERA_H
