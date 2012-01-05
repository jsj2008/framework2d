#include "EntityPlaceEvent.h"
#include <Log/Log.h>
#include <AbstractFactory/FactoryParameters.h>

EntityPlaceEvent::EntityPlaceEvent(Entity* _entity, std::string& _factoryName, FactoryParameters* _parameters)
{
    //ctor
    entity = _entity;
    factoryName = _factoryName;
    parameters = _parameters;
    char buffer[64];
    const char* name = parameters->get<std::string>("name", "error").c_str();
    sprintf(buffer, "%s placed %p", name, _entity);
    g_Log.message(buffer);
}

EntityPlaceEvent::EntityPlaceEvent(const EntityPlaceEvent& rhs)
{
    entity = rhs.entity;
    factoryName = rhs.factoryName;
    parameters = new FactoryParameters(*rhs.parameters);
}

EntityPlaceEvent::~EntityPlaceEvent()
{
    //dtor
}
