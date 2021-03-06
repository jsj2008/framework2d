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
        Entity* getEntity();

        const Vec2f& getPosition();
        float getAngle();
        void applyLinearImpulse(const Vec2f& _impulse); /// Center point
        void applyLinearImpulse(const Vec2f& _impulse, const Vec2f& _point);
        Vec2f getLinearVelocity();
        float getDensity();
        float getArea();
        float getAreaBelowLine(float _height);
    protected:
    private:
};

#endif // JOINTBODYPART_H
