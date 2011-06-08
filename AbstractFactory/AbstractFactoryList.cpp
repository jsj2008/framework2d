#include "AbstractFactoryList.h"
#include <AbstractFactory/Factories/ExplosionFactory.h>
#include <AbstractFactory/Factories/ProjectileFactory.h>
#include <AbstractFactory/Factories/ParticleFactory.h>
#include <AbstractFactory/Factories/CrateFactory.h>
#include <AbstractFactory/Factories/LevelGeometryFactory.h>
#include <AbstractFactory/Factories/AIEntityFactory.h>
#include <AbstractFactory/Factories/BubbleFactory.h>
#include <Entities/Bubbles/AllBubbles.h>
#include <AbstractFactory/FactoryLoader.h>
#include <cassert>
AbstractFactoryList g_AbstractFactoryList;

class FactoryCreator
{
    public:
        virtual AbstractFactory* createFactory(FactoryLoader* loader)=0;
};

AbstractFactoryList::AbstractFactoryList()
{
    //ctor
    registerFactoryType<ExplosionFactory>("ExplosionFactory");
    registerFactoryType<ProjectileFactory>("ProjectileFactory");
    registerFactoryType<ParticleFactory>("ParticleFactory");
    registerFactoryType<CrateFactory>("CrateFactory");
    registerFactoryType<LevelGeometryFactory>("LevelGeometryFactory");
    registerFactoryType<AIEntityFactory>("AIEntityFactory");
    registerFactoryType<BubbleFactory<SuctionBubble>>("SuctionBubble");
    registerFactoryType<BubbleFactory<UpwardsGravityBubble>>("UpwardsGravityBubble");
    FactoryLoader loader("Resources/Factories.txt");
    while (loader.next())
    {
        assert(factories.find(loader.getName()) == factories.end());
        factories[loader.getName()] = factoryCreators[loader.getType()]->createFactory(&loader);
        loader.end();
    }
}

AbstractFactoryList::~AbstractFactoryList()
{
    //dtor
}

void AbstractFactoryList::addFactory(AbstractFactoryReference name, AbstractFactory* factory)
{
}

Entity* AbstractFactoryList::useFactory(AbstractFactoryReference factory, FactoryParameters* parameters)
{
    if (parameters == NULL)
    {
        FactoryParameters params;
        params.add<Vec2f>("dickhole",Vec2f(0,0));
        return factories[factory]->useFactory(&params);
        params.clear();
    }
    else
    {
        return factories[factory]->useFactory(parameters);
    }
}

template <typename T>
class TemplateFactoryCreator : public FactoryCreator
{
    public:
        AbstractFactory* createFactory(FactoryLoader* loader){return new T(loader);}
};

template <typename T>
void AbstractFactoryList::registerFactoryType(const std::string& name)
{
    factoryCreators[name] = new TemplateFactoryCreator<T>;
}
