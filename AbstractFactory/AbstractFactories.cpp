#include "AbstractFactories.h"

AbstractFactories::AbstractFactories()
{
    //ctor
    physicsManager = nullptr;
}

AbstractFactories::~AbstractFactories()
{
    //dtor
}


void AbstractFactories::setWorld(PhysicsManager* _world)
{
    physicsManager = _world;
}
void AbstractFactories::init()
{
    for (auto i = productTypeList().begin(); i != productTypeList().end(); i++)
    {
        ProductType* productType = i->second;
        unsigned int id = productType->getProductId();
        while (id >= indexedFactoryLists.size())
        {
            indexedFactoryLists.resize(id+1);
        }
        AbstractFactoryListBase* list = productType->createFactoryList(this);
        indexedFactoryLists[id] = list;
        attachChild(list);
        //i->second->init(this);
    }
}

void AbstractFactories::addFactory(const std::string& _product, FactoryLoader* _loader)
{
    ProductType* type = productTypeList()[_product];
    indexedFactoryLists[type->getProductId()]->addFactory(this, _loader);
}

void AbstractFactories::registerActions()
{
}

/*UntypedAbstractFactory* AbstractFactories::getUntypedFactory(const std::string& type, const std::string& name)
{
    return (*getFactoryListList())[type]->getUntypedFactory(name);
}*/

PhysicsManager* AbstractFactories::getWorld()
{
    return physicsManager;
}
