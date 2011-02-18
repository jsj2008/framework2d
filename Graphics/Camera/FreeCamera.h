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
        void updateTransform(int xRes, int yRes);
        void trigger(InputActions actions);
        void registerWithInputState(InputState* inputState);
    protected:
    private:
        int xPos, yPos;
};

#endif // FREECAMERA_H
