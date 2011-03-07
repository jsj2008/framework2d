#ifndef FREECAMERA_H
#define FREECAMERA_H

#include "Camera.h"
#include <Input/EventListener.h>

class FreeCamera : public Camera, public EventListener
{
    public:
        FreeCamera();
        virtual ~FreeCamera();
        void updateTransform(Vec2i resolution);
        void trigger(InputActions actions);
        void activate();
    protected:
    private:
        Vec2i position;
};

#endif // FREECAMERA_H
