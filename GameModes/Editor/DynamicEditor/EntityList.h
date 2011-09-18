#ifndef ENTITYLIST_H
#define ENTITYLIST_H

class Entity;
#include <string>

class EntityList
{
    public:
        EntityList();
        virtual ~EntityList();
        void addEntity(Entity* _entity, const std::string& _displayName);
    protected:
    private:
};

#endif // ENTITYLIST_H
