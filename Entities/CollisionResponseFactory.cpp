#include "CollisionResponseFactory.h"

CollisionResponseFactory::CollisionResponseFactory()
{
    //ctor
}

CollisionResponseFactory::~CollisionResponseFactory()
{
    //dtor
}
#include <iostream>

void CollisionResponseFactory::init(FactoryLoader* _loader, AbstractFactories* factories)
{
    std::string handleName = _loader->getName();
    if (handleName == "")
        handleName = "CollisionResponse";
    bool sensor = _loader->get<bool>("isSensor", false);
    handle = factories->getCollisionDatabase()->createHandle(handleName, sensor);

    std::vector<std::string> filters = _loader->getArray<std::string>("filters", {});
    for (unsigned int i = 0; i < filters.size(); i++)
    {
        handle->addFilter(filters[i]);
    }

    std::string defaultAction = _loader->get<std::string>("defaultAction", "null");
    if (defaultAction != "null")
    {
        handle->setDefaultEvent(defaultAction);
    }

    std::vector<std::string> handles = _loader->getArray<std::string>("event__Collisions", {});
    std::vector<std::string> actions = _loader->getArray<std::string>("event__Actions", {});
    for (unsigned int i = 0; i < handles.size(); i++)
    {
        handle->addEvent(handles[i], actions[i]);
    }
}
CollisionResponse* CollisionResponseFactory::useFactory(FactoryParameters* _parameters)
{
    return new CollisionResponse(handle);
}
