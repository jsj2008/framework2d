#ifndef AIENTITY_H
#define AIENTITY_H

#include "Entity.h"
#include <AI/CharacterController.h>
#include <Box2D/Common/b2Math.h>
class Brain;
class Weapon;
template <typename Product>
class AbstractFactoryBase;

class AIEntity : public Entity
{
    public:
        AIEntity(Brain* _Brain, Weapon* _weapon, AbstractFactoryBase<Entity>* _damageSprayFactory);
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
        AbstractFactoryBase<Entity>* damageSprayFactory;
};

#endif // AIENTITY_H
