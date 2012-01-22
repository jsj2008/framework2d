#include "CollisionResponseFactory.h"

CollisionResponseFactory::CollisionResponseFactory()
{
    //ctor
}

CollisionResponseFactory::~CollisionResponseFactory()
{
    //dtor
}

void CollisionResponseFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    std::string handleName = loader->get<std::string>("Name", "Default");
    handle = factories->getCollisionDatabase()->getHandle(handleName);
    attachChild(handle); /// FIXME this is silly

    std::vector<std::string> filters = loader->getArray<std::string>("filters", {});
    for (unsigned int i = 0; i < filters.size(); i++)
    {
        handle->addFilter(filters[i]);
    }

    std::string defaultAction = loader->get<std::string>("defaultAction", "null");
    if (defaultAction != "null")
    {
        handle->setDefaultEvent(defaultAction);
    }

    std::vector<std::string> handles = loader->getArray<std::string>("event__Collisions", {});
    std::vector<std::string> actions = loader->getArray<std::string>("event__Actions", {});
    for (unsigned int i = 0; i < handles.size(); i++)
    {
        handle->addEvent(handles[i], actions[i]);
    }
}
CollisionResponse* CollisionResponseFactory::useFactory(FactoryParameters* _parameters)
{
    return handle;
}
