#ifndef PHYSICSCAMERA_H
#define PHYSICSCAMERA_H

#include "Camera.h"
class Body;

class PhysicsCamera : public Camera
{
    public:
        PhysicsCamera(Body* _body);
        virtual ~PhysicsCamera();
        void updateTransform(Vec2i resolution);
        void activate();
    protected:
    private:
        Body* body;
};

#endif // PHYSICSCAMERA_H
