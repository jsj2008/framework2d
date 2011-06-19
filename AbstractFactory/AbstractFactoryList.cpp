#include "AbstractFactoryList.h"
#include <AbstractFactory/FactoryLoader.h>
#include <cassert>
AbstractFactoryList<Entity> g_AbstractFactoryList;


template <typename Product>
AbstractFactoryList<Product>::AbstractFactoryList()
{
    //ctor
    /*FactoryLoader loader("Resources/Factories.txt");
    while (loader.next())
    {
        assert(factories.find(loader.getName()) == factories.end());
        factories[loader.getName()] = factoryCreators[loader.getType()]->createFactory(&loader);
        loader.end();
    }*/
}

template <typename Product>
AbstractFactoryList<Product>::~AbstractFactoryList()
{
    //dtor
}

