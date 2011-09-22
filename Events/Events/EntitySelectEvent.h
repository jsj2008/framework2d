#ifndef ENTITYSELECTEVENT_H
#define ENTITYSELECTEVENT_H

#include <Events/Event.h>
class Entity;

class EntitySelectEvent : public Event
{
    public:
        EntitySelectEvent(Entity* _selectedEntity);
        virtual ~EntitySelectEvent();
        Entity* getSelectedEntity(){return selectedEntity;}
    protected:
    private:
        Entity* selectedEntity;
};

#endif // ENTITYSELECTEVENT_H
