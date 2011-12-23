#ifndef AIENTITY_H
#define AIENTITY_H

#include "Entity.h"
#include <Box2D/Common/b2Math.h>
class CharacterController;
class Brain;
class Weapon;
template <typename Product>
class AbstractFactoryBase;

class AIEntity : public Entity
{
    public:
        AIEntity();
        void init(Brain* _Brain, Weapon* _weapon, AbstractFactoryBase<Entity>* _damageSprayFactory, Skin* _skin);
        void update();
        /*void jump();
        void walkLeft();
        void walkRight();
        void stopWalking();*/
        void damage();
        void weaponBegin(Vec2f targetPosition);
        void weaponMove(Vec2f targetPosition);
        void weaponEnd(Vec2f targetPosition);
        void setController(CharacterController* _controller){controller = _controller;}
        CharacterController* getMoveControls(){return controller;}
        Brain* getBrain(){return mBrain;}
    protected:
    private:
        friend class CharacterController;
        friend class GeometrySelector; /// This is so it can prevent it from dying, should probably get a better way to do this FIXME
        void fire(Vec2f targetDirection);
        int health;
        virtual ~AIEntity();
        Brain* mBrain;
        CharacterController* controller;
        Weapon* weapon;
        AbstractFactoryBase<Entity>* damageSprayFactory;
};

#endif // AIENTITY_H
