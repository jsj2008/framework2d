#ifndef ENTITYPLACEEVENT_H
#define ENTITYPLACEEVENT_H

#include <Events/Event.h>
class Entity;
class FactoryParameters;

/**
    This is triggered when an entity is placed by the editor
    This corresponds with EntityRemoveEvent which is the opposite.
    These are also called when the actions occur as a result of undos/redos
*/
class EntityPlaceEvent : public Event
{
    public:
        EntityPlaceEvent(Entity* _entity, FactoryParameters* _parameters);
        virtual ~EntityPlaceEvent();
    protected:
    private:
        Entity* entity;
        FactoryParameters* parameters;
};

#endif // ENTITYPLACEEVENT_H
