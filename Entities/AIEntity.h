#ifndef AIENTITY_H
#define AIENTITY_H

#include "Entity.h"
#include <AI/CharacterController.h>
#include <Box2D/Common/b2Math.h>
class Brain;
class Weapon;

class AIEntity : public Entity
{
    public:
        AIEntity(Brain* _Brain);
        EntityType getType(){return eAIEntityType;}
        void update();
        void jump();
        void walkLeft();
        void walkRight();
        void stopWalking();
        void damage();
        void fireAt(Vec2f targetPosition);
        void setWheel(b2RevoluteJoint* _wheel){controller.setWheel(_wheel);}
    protected:
    private:
        friend class CharacterController;
        friend class GeometrySelector; /// This is so it can prevent it from dying, should probably get a better way to do this FIXME
        void fire(Vec2f targetDirection);
        int health;
        virtual ~AIEntity();
        Brain* mBrain;
        CharacterController controller;
        Weapon* weapon;
};

#endif // AIENTITY_H
