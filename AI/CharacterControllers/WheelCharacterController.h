#ifndef WHEELCHARACTERCONTROLLER_H
#define WHEELCHARACTERCONTROLLER_H

#include <AI/CharacterController.h>
class MotorPart;

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
        WheelCharacterController(AIEntity* _entity, Properties* _properties);
        virtual ~WheelCharacterController();
        void update();
        void booleanControls(int _button, bool _pressed);
        void setWheel(MotorPart* _wheel){wheel = _wheel;}
    protected:
    private:
        void booleanControlStart(int _button);
        void booleanControlEnd(int _button);
        void walkLeft();
        void walkRight();
        void stopWalking();
        void jump();
        MotorPart* wheel;
        unsigned short airbourneCounter;
        unsigned short jumpCounter;
        Properties* properties;
};

#endif // WHEELCHARACTERCONTROLLER_H
