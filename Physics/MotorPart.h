#ifndef MOTORPART_H
#define MOTORPART_H

#include <Physics/BodyPart.h>

class MotorPart : public BodyPart
{
    public:
        MotorPart();
        virtual ~MotorPart();
        void setMotorSpeed(float _speed);
    protected:
    private:
};

#endif // MOTORPART_H
