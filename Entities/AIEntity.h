#ifndef AIENTITY_H
#define AIENTITY_H

#include "Entity.h"
#include <Box2D/Common/b2Math.h>
class Brain;

class AIEntity : public Entity
{
    public:
        AIEntity(Brain* _Brain);
        virtual ~AIEntity();
        EntityType getType(){return eAIEntityType;}
        void update();
        void jump();
        void walkLeft();
        void walkRight();
    protected:
    private:
        Brain* mBrain;
        bool grounded;
        Vec2f groundNormal;
};

#endif // AIENTITY_H
