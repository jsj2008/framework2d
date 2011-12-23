#ifndef ENTITYLIST_H
#define ENTITYLIST_H

#include <Events/EventListener.h>
#include <Events/Events/EntityPlaceEvent.h>
#include <Events/Events/EntityRemoveEvent.h>
#include <Events/Events/EntitySelectEvent.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
namespace CEGUI
{
    class Combobox;
    class EventArgs;
    class Window;
}
class LevelEntity;

/// FIXME move this to Level
class EntityList : public EventsListener<EntityPlaceEvent>, public EventsListener<EntityRemoveEvent>, public EventsListener<EntitySelectEvent>
{
    public:
        EntityList(const std::string& _windowName, const std::string& _listFilename);
        virtual ~EntityList();
        void addEntity(LevelEntity* _entity, const std::string& _displayName);
        void removeEntity(LevelEntity* _entity);
        bool eventListSelectionChange(const CEGUI::EventArgs& _args);
        bool eventListItemSelected(const CEGUI::EventArgs& _args);
        bool filterDeadButton(const CEGUI::EventArgs& _args);
        void entityDied(LevelEntity* _entity);
        void saveLevel(const std::string& _listFilename);
    protected:
    private:
        void loadLevel(const std::string& _listFilename);
        bool trigger(EntityPlaceEvent* event);
        bool trigger(EntityRemoveEvent* event);
        bool trigger(EntitySelectEvent* event);
        CEGUI::Combobox* listBox;
        CEGUI::Window* selectionDisplay;
        std::unordered_map<Entity*,LevelEntity*> entityMap;
        bool filterDead;
        std::unordered_set<LevelEntity*> filteredDead;
};

#endif // ENTITYLIST_H
