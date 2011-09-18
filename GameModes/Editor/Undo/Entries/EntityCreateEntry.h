#ifndef ENTITYCREATEENTRY_H
#define ENTITYCREATEENTRY_H

#include <GameModes/Editor/Undo/UndoEntry.h>
#include <AbstractFactory/FactoryParameters.h>
#include <GameModes/Editor/Undo/UndoResources.h>
class Entity;
class Level;

class EntityCreateEntry : public UndoEntry
{
    public:
        EntityCreateEntry(const std::string& _factory, const std::string& _name, FactoryParameters* _params, Level* _level);
        ~EntityCreateEntry();
        void redo();
        void undo();
        const char* getListText();
        const char* getTooltipText();
    protected:
    private:
        UndoResource entity;
        std::string factory;
        std::string name;
        FactoryParameters params;
        Level* level;
};

#endif // ENTITYCREATEENTRY_H
