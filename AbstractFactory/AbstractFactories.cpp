#include "AbstractFactories.h"

AbstractFactories::AbstractFactories()
{
    //ctor
}

AbstractFactories::~AbstractFactories()
{
    //dtor
}


void AbstractFactories::init()
{
    std::unordered_map<std::string, class AbstractFactoryListBase*>* factoryLists = getFactoryListList();
    for (auto i = factoryLists->begin(); i != factoryLists->end(); i++)
    {
        i->second->init();
    }
}
