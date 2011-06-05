#include "FactoryList.h"
#include "Factory/AllFactories.h"
using namespace std;
FactoryList g_FactoryList;
FactoryList::FactoryList()
:factories({new ConvexGeometryFactory, new BubbleFactory, new AIEntityFactory})
{
    assert(factories.size() == eStandardFactoriesMax);
    //ctor
}

FactoryList::~FactoryList()
{
    //dtor
}

Entity* FactoryList::useFactory(StandardFactoryDef def, StandardFactories factoryType)
{
    Factory* factory = getFactory(def.type);
    return factory->createEntity(&def.baseDef);
}

/*Entity* FactoryList::useFactory(FactoryDef* data, StandardFactories factoryNum)
{
    Factory* factory = getFactory(factoryNum);
    return factory->createEntity(data);
}*/

Factory* FactoryList::getFactory(StandardFactories factory)
{
    return factories[factory];
}
StandardFactoryDef::StandardFactoryDef()
{
    type = eStandardFactoriesMax;
}
StandardFactoryDef::StandardFactoryDef(ConvexGeometryDef& def)
{
    convexGeometryDef = def;
    type = eConvexPolygonFactory;
}
StandardFactoryDef::StandardFactoryDef(BubbleDef& def)
{
    bubbleDef = def;
    type = eBubbleFactory;
}
StandardFactoryDef::StandardFactoryDef(AIEntityDef& def)
{
    aiEntityDef = def;
    type = eAIEntityFactory;
}























