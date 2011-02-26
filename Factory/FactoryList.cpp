#include "FactoryList.h"
#include "Factory/AllFactories.h"
using namespace std;
FactoryList g_FactoryList;
FactoryList::FactoryList()
:factories({new PlayerFactory, new ConvexGeometryFactory, new CrateFactory, new BubbleFactory})
{
    assert(factories[eStandardFactoriesMax-1]);
    //ctor
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
