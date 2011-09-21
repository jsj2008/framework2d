#ifndef ENTITYPLACEEVENT_H
#define ENTITYPLACEEVENT_H

#include <Events/Event.h>
#include <string>
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
        EntityPlaceEvent(Entity* _entity, std::string& _factoryName, FactoryParameters* _parameters);
        EntityPlaceEvent(const EntityPlaceEvent& rhs);
        virtual ~EntityPlaceEvent();
        const std::string& getFactoryName(){return factoryName;}
        FactoryParameters* getParameters(){return parameters;}
    protected:
    private:
        Entity* entity;
        std::string factoryName;
        FactoryParameters* parameters;
};

#endif // ENTITYPLACEEVENT_H
