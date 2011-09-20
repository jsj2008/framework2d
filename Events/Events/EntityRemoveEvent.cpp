#include "EntityRemoveEvent.h"
#include <Log/Log.h>

EntityRemoveEvent::EntityRemoveEvent(Entity* _entity, FactoryParameters* _parameters)
{
    //ctor
    entity = _entity;
    parameters = _parameters;
    char buffer[64];
    sprintf(buffer, "Entity removed %p", _entity);
    g_Log.message(buffer);
}

EntityRemoveEvent::~EntityRemoveEvent()
{
    //dtor
}
