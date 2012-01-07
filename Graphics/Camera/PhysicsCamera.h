#ifndef PHYSICSCAMERA_H
#define PHYSICSCAMERA_H

#include "Camera.h"
class BodyPart;

class PhysicsCamera : public Camera
{
    public:
        PhysicsCamera(BodyPart* _body);
        virtual ~PhysicsCamera();
        void updateTransform(Vec2i resolution);
        void activate();
    protected:
    private:
        BodyPart* body;
};

#endif // PHYSICSCAMERA_H
