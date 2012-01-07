#ifndef WHEELCHARACTERCONTROLLER_H
#define WHEELCHARACTERCONTROLLER_H

#include <AI/CharacterController.h>
class JointBodyPart;

class WheelCharacterController : public CharacterController
{
    public:
        struct Properties /// Should think of a way to fit this into a design pattern
        {
            float walkSpeed;
            float jumpHeight;
            float extraGravity;
            unsigned short jumpRecharge;
            unsigned short fallTolerance;
        };
        WheelCharacterController(JointBodyPart* _joint, Properties* _properties);
        virtual ~WheelCharacterController();
        void update();
        void booleanControls(int _button, bool _pressed);
    protected:
    private:
        void booleanControlStart(int _button);
        void booleanControlEnd(int _button);
        void walkLeft();
        void walkRight();
        void stopWalking();
        void jump();
        unsigned short airbourneCounter;
        unsigned short jumpCounter;
        Properties* properties;
        JointBodyPart* joint;
};

#endif // WHEELCHARACTERCONTROLLER_H
