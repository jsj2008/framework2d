#ifndef ENTITYDELETEENTRY_H
#define ENTITYDELETEENTRY_H

#include <string>
#include <GameModes/Editor/Undo/UndoEntry.h>
#include <GameModes/Editor/Undo/UndoResources.h>
#include <AbstractFactory/FactoryParameters.h>
class Entity;
class Level;

class EntityDeleteEntry : public UndoEntry
{
    public:
        EntityDeleteEntry(Entity* _entityPtr, Level* _level);
        ~EntityDeleteEntry();
        void redo();
        void undo();
        const char* getListText();
        const char* getTooltipText();
    protected:
    private:
        UndoResource entity;
        Level* level;
        std::pair<std::string,FactoryParameters> saveConstruction;
};

#endif // ENTITYDELETEENTRY_H
