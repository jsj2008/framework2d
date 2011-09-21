#ifndef ENTITYLIST_H
#define ENTITYLIST_H

#include <Events/EventListener.h>
#include <Events/Events/EntityPlaceEvent.h>
#include <Events/Events/EntityRemoveEvent.h>
#include <string>
namespace CEGUI
{
    class Combobox;
}
class Entity;

class EntityList : public EventsListener<EntityPlaceEvent>, public EventsListener<EntityRemoveEvent>
{
    public:
        EntityList(const std::string& _windowName);
        virtual ~EntityList();
        void addEntity(Entity* _entity, const std::string& _displayName);
        bool trigger(EntityPlaceEvent* event);
        bool trigger(EntityRemoveEvent* event);
    protected:
    private:
        CEGUI::Combobox* listBox;
        // std::unordered_map<std::string,Entity*> entityMap; Needs a double deference
};

#endif // ENTITYLIST_H
