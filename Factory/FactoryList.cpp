#include "FactoryList.h"
#include "Factory/AllFactories.h"
using namespace std;
FactoryList g_FactoryList;
FactoryList::FactoryList()
:factories({new ConvexGeometryFactory, new CrateFactory, new BubbleFactory, new ParticleFactory, new AIEntityFactory, new ProjectileFactory})
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
StandardFactoryDef::StandardFactoryDef()
{
    type = eStandardFactoriesMax;
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
StandardFactoryDef::StandardFactoryDef(AIEntityDef& def)
{
    aiEntityDef = def;
    type = eAIEntityFactory;
}
StandardFactoryDef::StandardFactoryDef(ParticleDef& def)
{
    particleDef = def;
    type = eParticleFactory;
}
StandardFactoryDef::StandardFactoryDef(ProjectileDef& def)
{
    projectileDef = def;
    type = eProjectileFactory;
}

































