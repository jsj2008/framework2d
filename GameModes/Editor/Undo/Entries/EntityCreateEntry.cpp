#include "EntityCreateEntry.h"
#include <Level/Level.h>
#include <Level/LevelEntity.h>
#include <Events/Events.h>
#include <Events/Events/EntityPlaceEvent.h>
#include <Events/Events/EntityRemoveEvent.h>
#include <sstream>
#include <cstring>

EntityCreateEntry::EntityCreateEntry(LevelEntity* _entity, Level* _level)
{
    //ctor
    level = _level;
    entity = _entity;
}

EntityCreateEntry::~EntityCreateEntry()
{
    //dtor
}

/*Entity* EntityCreateEntry::getEntity()
{
    Entity* ret = static_cast<Entity*>(UndoResources::global().getValue(entity));
    if (ret == nullptr)
    {
        throw -1;
    }
    return ret;
}*/
void EntityCreateEntry::redo()
{
    entity->createEntity();
    //UndoResources::global().setValue(entity, entityPtr);
    //EntityPlaceEvent event(entityPtr, factory, &params);
    //Events::global().triggerEvent(&event);
}
void EntityCreateEntry::undo()
{
    //EntityRemoveEvent event(entityPtr, factory, &params);
    //Events::global().triggerEvent(&event);
    entity->destroyEntity();
}

const char* EntityCreateEntry::getListText()
{
    static std::string listText = "Create ";
    listText = std::string("Create ") + entity->getName();
    return listText.c_str();
}

const char* EntityCreateEntry::getTooltipText()
{
    /*static std::stringstream text;
    text.str("");
    text << params;
    return text.str().c_str();*/
    throw -1;
}
