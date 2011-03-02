#include "FactoryList.h"
#include "Factory/AllFactories.h"
using namespace std;
FactoryList g_FactoryList;
FactoryList::FactoryList()
:factories({new PlayerFactory, new ConvexGeometryFactory, new CrateFactory, new BubbleFactory, new ParticleFactory})
{
    assert(factories[eStandardFactoriesMax-1]);
    //ctor
}

FactoryList::~FactoryList()
{
    //dtor
}

Entity* FactoryList::useFactory(StandardFactoryDef def, StandardFactories factoryType)
{
    assert(factoryType == def.type);
    Factory* factory = getFactory(def.type);
    return factory->createEntity(&def.crateDef);
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

StandardFactoryDef::StandardFactoryDef(PlayerDef& def)
{
    playerDef = def;
    type = ePlayerFactory;
}
StandardFactoryDef::StandardFactoryDef(CrateDef& def)
{
    crateDef = def;
    type = eCrateFactory;
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
StandardFactoryDef::StandardFactoryDef(ParticleDef& def)
{
    particleDef = def;
    type = eParticleFactory;
}
