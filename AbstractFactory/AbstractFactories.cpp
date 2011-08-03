#include "AbstractFactories.h"
#include <iostream>

AbstractFactories::AbstractFactories()
{
    //ctor
    physicsManager = nullptr;
}

AbstractFactories::~AbstractFactories()
{
    //dtor
}


void AbstractFactories::init(PhysicsManager* _world)
{
    physicsManager = _world;
    std::unordered_map<std::string, class AbstractFactoryListBase*>* factoryLists = getFactoryListList();
    for (auto i = factoryLists->begin(); i != factoryLists->end(); i++)
    {
        i->second->init(this);
    }
}

void AbstractFactories::print()
{
    for (auto i = getFactoryListList()->begin(); i != getFactoryListList()->end(); i++)
    {
        i->second->print();
    }
}


UntypedAbstractFactory* AbstractFactories::getUntypedFactory(const std::string& type, const std::string& name)
{
    return (*getFactoryListList())[type]->getUntypedFactory(name);
}

PhysicsManager* AbstractFactories::getWorld()
{
    return physicsManager;
}
