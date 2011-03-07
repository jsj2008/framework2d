#ifndef PHYSICSCAMERA_H
#define PHYSICSCAMERA_H

#include "Camera.h"
class b2Body;

class PhysicsCamera : public Camera
{
    public:
        PhysicsCamera(b2Body* _body);
        virtual ~PhysicsCamera();
        void updateTransform(Vec2i resolution);
        void activate();
    protected:
    private:
        b2Body* body;
};

#endif // PHYSICSCAMERA_H
