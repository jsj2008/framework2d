#ifndef LEVELENTITY_H
#define LEVELENTITY_H

#include <Events/EventListener.h>
#include <Events/Events/EntityDeathEvent.h>
#include <AbstractFactory/FactoryParameters.h>
#include <string>
class EntityList;
class Entity;
template <typename Product>
class AbstractFactoryBase;
namespace CEGUI
{
    class ListboxTextItem;
    class Window;
    class EventArgs;
}

class LevelEntity : public EventsListener<EntityDeathEvent>
{
    public:
        LevelEntity(EntityList* _entityList, FactoryParameters* _parameters, const std::string& _factoryName);
        virtual ~LevelEntity();
        bool trigger(EntityDeathEvent* _event);
        bool entityIsAlive(){return entity != nullptr;}
        Entity* getEntity(){return entity;}
        bool isNamed();
        Entity* createEntity();
        void destroyEntity();
        std::string getName();
        void setListBoxItem(CEGUI::ListboxTextItem* _item){listBoxItem = _item;}
        CEGUI::ListboxTextItem* getListBoxItem(){return listBoxItem;}
        void show();
        void activateDisplay(CEGUI::Window* _window);
        void output(std::ofstream* _file);
    protected:
    private:
        bool quitButton(const CEGUI::EventArgs& _args);
        EntityList* entityList;
        FactoryParameters parameters;
        AbstractFactoryBase<Entity>* factory;
        std::string factoryName;
        Entity* entity;
        CEGUI::ListboxTextItem* listBoxItem;
};

#endif // LEVELENTITY_H
