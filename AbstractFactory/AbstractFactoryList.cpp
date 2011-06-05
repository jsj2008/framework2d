#include "AbstractFactoryList.h"
#include <AbstractFactory/Factories/ExplosionFactory.h>
#include <AbstractFactory/Factories/ProjectileFactory.h>
#include <AbstractFactory/Factories/ParticleFactory.h>
#include <AbstractFactory/Factories/CrateFactory.h>
#include <AbstractFactory/FactoryLoader.h>
#include <cassert>
AbstractFactoryList g_AbstractFactoryList;

AbstractFactoryList::AbstractFactoryList()
{
    //ctor
    registerFactoryType<ExplosionFactory>("ExplosionFactory");
    FactoryLoader loader("Resources/Factories.txt");
    loader.next();
    addFactory("explosion", new ExplosionFactory(&loader));
    loader.end();
    addFactory("grenade", new ProjectileFactory);
    addFactory("spark", new ParticleFactory(1.0f,60));
    addFactory("crate", new CrateFactory("player",1.0f));
}
/*
    std::ifstream file;
    file.open("explosion");
    addFactory("explosion", new ExplosionFactory(&file));
    file.open("grenade");
    addFactory("grenade", new ProjectileFactory(&file));
    file.open("spark");
    addFactory("spark", new ParticleFactory(&file));//(1.0f,60));
    file.open("crate");
    addFactory("crate", new CrateFactory(&file));//("player",1.0f));*/

AbstractFactoryList::~AbstractFactoryList()
{
    //dtor
}

void AbstractFactoryList::addFactory(AbstractFactoryReference name, AbstractFactory* factory)
{
    assert(factories.find(name) == factories.end());
    factories[name] = factory;
}

Entity* AbstractFactoryList::useFactory(AbstractFactoryReference factory, FactoryParameters* parameters)
{
    return factories[factory]->useFactory(parameters);
}

class FactoryCreator
{
    public:
        virtual AbstractFactory* createFactory(FactoryLoader* loader)=0;
};
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
