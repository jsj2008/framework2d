#include "EntityCreateEntry.h"
#include <Level/Level.h>
#include <sstream>
#include <cstring>

EntityCreateEntry::EntityCreateEntry(const std::string& _factory, const std::string& _name, FactoryParameters* _params, Level* _level)
{
    //ctor
    factory = _factory;
    name = _name;
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
    static std::string listText = "Create ";
    listText = std::string("Create ") + name;
    return listText.c_str();
}

const char* EntityCreateEntry::getTooltipText()
{
    static std::stringstream text;
    text.str("");
    text << params;
    return text.str().c_str();
}
