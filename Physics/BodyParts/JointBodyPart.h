#ifndef JOINTBODYPART_H
#define JOINTBODYPART_H

#include <Physics/BodyParts/BodyPart.h>
class b2RevoluteJoint;

class JointBodyPart : public BodyPart
{
    public:
        JointBodyPart(b2RevoluteJoint* _joint);
        virtual ~JointBodyPart();
        void setMotorSpeed(float _speed);
        void setMotorEnabled(bool _enabled);
        void setMotorTorque(float _torque);
    protected:
    private:
};

#endif // JOINTBODYPART_H
