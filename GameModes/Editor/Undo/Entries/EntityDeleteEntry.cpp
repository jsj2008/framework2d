#include "EntityDeleteEntry.h"
#include <Level/Level.h>
#include <sstream>
#include <cstring>

EntityDeleteEntry::EntityDeleteEntry(Entity* _entityPtr, Level* _level)
{
    //ctor
    entity = UndoResources::global().getEntrySafely(static_cast<void*>(_entityPtr));
    level = _level;
}

EntityDeleteEntry::~EntityDeleteEntry()
{
    //dtor
}

void EntityDeleteEntry::redo()
{
    Entity* entityPtr = static_cast<Entity*>(UndoResources::global().getValue(entity));
    level->removeBody(entityPtr, &saveConstruction);
    UndoResources::global().setValue(entity, nullptr); //Not necessary without destroying events backwards
}
void EntityDeleteEntry::undo()
{
    Entity* entityPtr = level->addBody(saveConstruction.first, &saveConstruction.second);
    UndoResources::global().setValue(entity, entityPtr);
}


const char* EntityDeleteEntry::getListText()
{
    static char listText[32] = "Delete ";
    memcpy(listText + strlen("Delete "), &saveConstruction.first[0], saveConstruction.first.length());
    return listText;
}

const char* EntityDeleteEntry::getTooltipText()
{
    static std::stringstream text;
    text.str("");
    text << saveConstruction.second;
    return text.str().c_str();
}
