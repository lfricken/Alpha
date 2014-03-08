#ifndef CAMERA_H
#define CAMERA_H
#include <stdafx.h>

class Camera
{
    public:
        Camera();
        virtual ~Camera();

        sf::View& getView();
        const float& getZoomLevel();
        void setZoomLevel(float newZoom);
        void zoomFactor(float zoomChange);

        bool isTracking();
        bool toggleTracking();
    protected:
    private:
        bool m_isTracking;
        float m_zoomLevel;
        sf::View m_view;
};

#endif // CAMERA_H
