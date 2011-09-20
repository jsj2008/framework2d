#ifndef ENTITYLIST_H
#define ENTITYLIST_H

namespace CEGUI
{
    class Combobox;
}
class Entity;
#include <string>

class EntityList
{
    public:
        EntityList(const std::string& _windowName);
        virtual ~EntityList();
        void addEntity(Entity* _entity, const std::string& _displayName);
    protected:
    private:
        CEGUI::Combobox* listBox;
};

#endif // ENTITYLIST_H
