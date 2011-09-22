#ifndef SHOWENTITYEVENT_H
#define SHOWENTITYEVENT_H

#include <Events/Event.h>
class Entity;

/**
    This is the event fired when the camera in the editor should show a certain entity to the player
    Could be used for in-game stuff as well
*/
class ShowEntityEvent : public Event
{
    public:
        ShowEntityEvent(Entity* _entity);
        virtual ~ShowEntityEvent();
        Entity* getEntity(){return entity;}
    protected:
    private:
        Entity* entity;
};

#endif // SHOWENTITYEVENT_H
