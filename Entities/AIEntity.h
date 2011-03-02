#ifndef AIENTITY_H
#define AIENTITY_H

#include "Entity.h"
#include <Box2D/Common/b2Math.h>
class Brain;

class AIEntity : public Entity
{
    public:
        AIEntity(Brain* _Brain);
        EntityType getType(){return eAIEntityType;}
        void update();
        void jump();
        void walkLeft();
        void walkRight();
        void damage();
    protected:
    private:
        int health;
        virtual ~AIEntity();
        Brain* mBrain;
        bool grounded;
        Vec2f groundNormal;
};

#endif // AIENTITY_H
