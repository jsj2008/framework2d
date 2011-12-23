#ifndef FREECAMERA_H
#define FREECAMERA_H

#include "Camera.h"
#include <Input/EventListener.h>
#include <Events/EventListener.h>
#include <Events/Events/ShowEntityEvent.h>

class FreeCamera : public Camera, public EventListener, public EventsListener<ShowEntityEvent>
{
    public:
        FreeCamera();
        virtual ~FreeCamera();
        void updateTransform(Vec2i resolution);
        void resetInput();
        void trigger(InputActions actions, bool _pressed);
        void activate();
        bool trigger(ShowEntityEvent* _event);
    protected:
    private:
        Vec2i position;
        Vec2f bias;
        bool enableBias;
};

#endif // FREECAMERA_H
