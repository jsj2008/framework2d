#include "AbstractFactories.h"
#include <iostream>

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

void AbstractFactories::print(std::ostream* stream)
{
    for (auto i = getFactoryListList()->begin(); i != getFactoryListList()->end(); i++)
    {
        i->second->print(stream);
        *stream << std::endl;
    }
}


UntypedAbstractFactory* AbstractFactories::getUntypedFactory(const std::string& type, const std::string& name)
{
    return (*getFactoryListList())[type]->getUntypedFactory(name);
}
