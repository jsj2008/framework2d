#ifndef AIENTITY_H
#define AIENTITY_H

#include "Entity.h"
class Brain;

class AIEntity : public Entity
{
    public:
        AIEntity(Brain* _Brain);
        virtual ~AIEntity();
        EntityType getType(){return eAIEntityType;}
        void update();
    protected:
    private:
        Brain* mBrain;
};

#endif // AIENTITY_H
