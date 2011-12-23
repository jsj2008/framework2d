#ifndef ENTITYREMOVEEVENT_H
#define ENTITYREMOVEEVENT_H

#include <Events/Event.h>
#include <string>
class Entity;
class FactoryParameters;

/**
    See EntityPlaceEvent
*/

class EntityRemoveEvent : public Event
{
    public:
        EntityRemoveEvent(Entity* _entity, const std::string& _factoryName, FactoryParameters* _parameters);
        virtual ~EntityRemoveEvent();
        FactoryParameters* getParameters(){return parameters;}
        const std::string& getFactoryName(){return factoryName;}
    protected:
    private:
        Entity* entity;
        std::string factoryName;
        FactoryParameters* parameters;
};

#endif // ENTITYREMOVEEVENT_H
