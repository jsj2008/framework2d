#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H

#include <GameObject.h>
class AIEntity;
class b2RevoluteJoint;

class CharacterController : public GameObject<CharacterController>
{
    public:
        CharacterController(unsigned char _booleanButtonsSize, const char** _booleanButtonsNames);
        virtual ~CharacterController();
        virtual void update()=0;
        /*virtual void walkLeft()=0;
        virtual void walkRight()=0;
        virtual void stopWalking()=0;
        virtual void jump()=0;*/
        virtual void booleanControls(int _button, bool _pressed)=0;
        unsigned char getBooleanButtonsSize(){return booleanButtonsSize;}
        const char* getBoolButtonsName(unsigned char _index){return booleanButtonsNames[_index];}

        static void registerActions();
        void setAIEntity(AIEntity* _entity);
    protected:
        AIEntity* entity;
    private:
        unsigned char booleanButtonsSize;
        const char** booleanButtonsNames;
};

#endif // CHARACTERCONTROLLER_H
