#ifndef DEATHEVENT_H
#define DEATHEVENT_H

#include <Events/InstanceEvents/InstanceEvent.h>

template <typename DeadClass>
class DeathEvent : public InstanceEvent<DeathEvent<DeadClass>>
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
#endif // DEATHEVENT_H
