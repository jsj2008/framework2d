#ifndef ENTITYDEATHEVENT_H
#define ENTITYDEATHEVENT_H

#include <Events/Event.h>

template <typename DeadClass>
class DeathEvent : public Event
{
    public:
        DeathEvent(DeadClass* _entity);
        virtual ~DeathEvent();
        DeadClass* getEntity(){return entity;}
    protected:
    private:
        DeadClass* entity;
};

class Entity;
typedef DeathEvent<Entity> EntityDeathEvent;


template <typename DeadClass>
DeathEvent<DeadClass>::DeathEvent(DeadClass* _entity)
{
    //ctor
    entity = _entity;
}

template <typename DeadClass>
DeathEvent<DeadClass>::~DeathEvent()
{
    //dtor
}

#endif // ENTITYDEATHEVENT_H
