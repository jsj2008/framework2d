#ifndef PLAYERONECREATED_H
#define PLAYERONECREATED_H

#include <Events/SingletonEvents/SingletonEvent.h>
class AIEntity;

class PlayerOneCreated : public SingletonEvent<PlayerOneCreated>
{
    public:
        PlayerOneCreated(AIEntity* _entity);
        virtual ~PlayerOneCreated();
        AIEntity* getPlayer(){return entity;}
    protected:
    private:
        AIEntity* entity;
};

#endif // PLAYERONECREATED_H
