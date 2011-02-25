#include "FactoryList.h"
#include "Factory/AllFactories.h"
using namespace std;

FactoryList::FactoryList()
{
    //ctor
    factories["Platform"] = (new ConvexGeometryFactory);
}

FactoryList::~FactoryList()
{
    //dtor
}

Entity* FactoryList::useFactory(FactoryDef* data, StandardFactories factoryNum)
{
    Factory* factory = getFactory(factoryNum);
    return factory->createEntity(data);
}

Factory* FactoryList::getFactory(StandardFactories factory)
{
    return factories[factory];
}
