#include "EntityCreateEntry.h"
#include <Level/Level.h>

EntityCreateEntry::EntityCreateEntry(const std::string& _factory, FactoryParameters* _params, Level* _level)
{
    //ctor
    factory = _factory;
    params = *_params;
    level = _level;
    entity = UndoResources::global().createEntry();
}

EntityCreateEntry::~EntityCreateEntry()
{
    //dtor
}

void EntityCreateEntry::redo()
{
    Entity* entityPtr = level->addBody(factory,&params);
    UndoResources::global().setValue(entity, entityPtr);
}
void EntityCreateEntry::undo()
{
    Entity* entityPtr = static_cast<Entity*>(UndoResources::global().getValue(entity));
    level->removeBody(entityPtr);
}

const char* EntityCreateEntry::getListText()
{
    return "Create entity";
}
