#ifndef ENTITYCREATEENTRY_H
#define ENTITYCREATEENTRY_H

#include <GameModes/Editor/Undo/UndoEntry.h>
#include <AbstractFactory/FactoryParameters.h>
#include <GameModes/Editor/Undo/UndoResources.h>
class LevelEntity;
class Level;
class Entity;

class EntityCreateEntry : public UndoEntry
{
    public:
        EntityCreateEntry(LevelEntity* _entity, Level* _level);
        ~EntityCreateEntry();
        void redo();
        void undo();
        const char* getListText();
        const char* getTooltipText();
        Entity* getEntity();
    protected:
    private:
        LevelEntity* entity;
        Level* level;
};

#endif // ENTITYCREATEENTRY_H
