#ifndef WHEELCHARACTERCONTROLLER_H
#define WHEELCHARACTERCONTROLLER_H

#include <AI/CharacterController.h>


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
        void walkLeft();
        void walkRight();
        void stopWalking();
        void jump();
        void setWheel(b2RevoluteJoint* _wheel){wheel = _wheel;}
    protected:
    private:
        b2RevoluteJoint* wheel;
        unsigned short airbourneCounter;
        unsigned short jumpCounter;
        Properties* properties;
};

#endif // WHEELCHARACTERCONTROLLER_H
