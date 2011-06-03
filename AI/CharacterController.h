#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H

class AIEntity;
class b2RevoluteJoint;

class CharacterController
{
    public:
        CharacterController(AIEntity* _entity);
        virtual ~CharacterController();
        void update();
        void walkLeft();
        void walkRight();
        void stopWalking();
        void jump();
        void setWheel(b2RevoluteJoint* _wheel){wheel = _wheel;}
    protected:
    private:
        AIEntity* entity;
        b2RevoluteJoint* wheel;
        unsigned short airbourneCounter;
        unsigned short jumpCounter;
};

#endif // CHARACTERCONTROLLER_H
