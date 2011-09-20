#ifndef ENTITYREMOVEEVENT_H
#define ENTITYREMOVEEVENT_H

#include <Events/Event.h>
class Entity;
class FactoryParameters;

/**
    See EntityPlaceEvent
*/

class EntityRemoveEvent : public Event
{
    public:
        EntityRemoveEvent(Entity* _entity, FactoryParameters* _parameters);
        virtual ~EntityRemoveEvent();
    protected:
    private:
        Entity* entity;
        FactoryParameters* parameters;
};

#endif // ENTITYREMOVEEVENT_H
