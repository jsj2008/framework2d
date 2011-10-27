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
        indexedFactoryLists[id] = productType->createFactoryList(this);
        //i->second->init(this);
    }
}

/*UntypedAbstractFactory* AbstractFactories::getUntypedFactory(const std::string& type, const std::string& name)
{
    return (*getFactoryListList())[type]->getUntypedFactory(name);
}*/

PhysicsManager* AbstractFactories::getWorld()
{
    return physicsManager;
}
