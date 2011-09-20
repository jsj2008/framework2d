#include "EntityPlaceEvent.h"
#include <Log/Log.h>
#include <AbstractFactory/FactoryParameters.h>

EntityPlaceEvent::EntityPlaceEvent(Entity* _entity, FactoryParameters* _parameters)
{
    //ctor
    entity = _entity;
    parameters = _parameters;
    char buffer[64];
    const char* name = _parameters->get<std::string>("name", "error").c_str();
    sprintf(buffer, "%s placed %p", name, _entity);
    g_Log.message(buffer);
}

EntityPlaceEvent::~EntityPlaceEvent()
{
    //dtor
}
