#include "EntityDeleteEntry.h"
#include <Level/Level.h>
#include <Events/Events.h>
#include <Events/Events/EntityPlaceEvent.h>
#include <Events/Events/EntityRemoveEvent.h>
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
    EntityRemoveEvent event(entityPtr, &saveConstruction.second);
    Events::global().triggerEvent(&event);
    level->removeBody(entityPtr, &saveConstruction);
    UndoResources::global().setValue(entity, nullptr); //Not necessary without destroying events backwards
}
void EntityDeleteEntry::undo()
{
    Entity* entityPtr = level->addBody(saveConstruction.first, &saveConstruction.second);
    UndoResources::global().setValue(entity, entityPtr);
    EntityPlaceEvent event(entityPtr, &saveConstruction.second);
    Events::global().triggerEvent(&event);
}


const char* EntityDeleteEntry::getListText()
{
    static char listText[32] = "Delete ";
    strcpy(listText + strlen("Delete "), &saveConstruction.first[0]);
    return listText;
}

const char* EntityDeleteEntry::getTooltipText()
{
    /*static std::stringstream text;
    text.str("");
    text << saveConstruction.second;
    return text.str().c_str();*/
    return saveConstruction.first.c_str();
}
