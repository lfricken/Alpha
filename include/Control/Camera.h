#ifndef CAMERA_H
#define CAMERA_H

#include "stdafx.h"

class Camera
{
    public:
        Camera();
        virtual ~Camera();

        sf::View& getView();
        const sf::View& getView() const;

        const float& getZoomLevel() const;
        void setZoomLevel(float newZoom);
        void zoomFactor(float zoomChange);

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
