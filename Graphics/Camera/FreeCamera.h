#ifndef FREECAMERA_H
#define FREECAMERA_H

#include "Camera.h"
#include <Input/EventListener.h>
class InputState;

class FreeCamera : public Camera, public EventListener
{
    public:
        FreeCamera(InputState* inputState);
        virtual ~FreeCamera();
        void updateTransform(Vec2i resolution);
        void trigger(InputActions actions);
        void registerWithInputState(InputState* inputState);
    protected:
    private:
        Vec2i position;
};

#endif // FREECAMERA_H
