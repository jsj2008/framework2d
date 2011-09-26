#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H

class AIEntity;
class b2RevoluteJoint;

class CharacterController
{
    public:
        CharacterController(AIEntity* _entity);
        virtual ~CharacterController();
        virtual void update()=0;
        virtual void walkLeft()=0;
        virtual void walkRight()=0;
        virtual void stopWalking()=0;
        virtual void jump()=0;
        void registerDeathListener(void*){throw -1;}
    protected:
        AIEntity* entity;
    private:
};

#endif // CHARACTERCONTROLLER_H
