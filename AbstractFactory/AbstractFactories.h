#ifndef ABSTRACTFACTORIES_H
#define ABSTRACTFACTORIES_H

#include <GameObject.h>
#include <Entities/CollisionDatabase.h>
#include <string>
#include <vector>
#include <cassert>
#include <unordered_map>
typedef std::string AbstractFactoryReference;
template <typename Product>
class AbstractFactoryList;
template <typename Product>
class AbstractFactoryBase;
class FactoryParameters;
class UntypedAbstractFactory;
template <typename DerivedEvent>
class EventsListener;
class FactoryLoader;
class AbstractFactoryListBase;
class PhysicsManager;

class AbstractFactories : public GameObject<AbstractFactories>
{
    public:
        AbstractFactories();
        ~AbstractFactories();
        void init();

        template <typename Product>
        Product* useFactory(AbstractFactoryReference factory, FactoryParameters* _parameters, GameObjectBase* _parent);

        template <typename Product, typename Factory>
        static void registerFactoryType();

        template <typename Product>
        void renameProduct(const std::string& name);

        template <typename Product>
        AbstractFactoryBase<Product>* getFactory(const std::string& name);

        template <typename Product>
        AbstractFactoryBase<Product>* addFactory(FactoryLoader* _loader);

        GameObjectBase* addFactory(const std::string& _product, FactoryLoader* _loader);

        /// For this function, considering storing all untyped factories in one list referenced by one parameter,
        /// if I start to use it enough. These are inefficient to create and use, but it will take a little more
        /// time and memory to maintain a list of all factories
        UntypedAbstractFactory* getUntypedFactory(const std::string& type, const std::string& name);


        void print();

        void setWorld(PhysicsManager* _world);
        PhysicsManager* getWorld();
        CollisionDatabase* getCollisionDatabase(){return &collisionDatabase;}

        static void registerActions();
    protected:
    private:
        class ProductType
        {
            public:
                ProductType(unsigned int& _productId){productId = _productId++;}
                virtual AbstractFactoryListBase* createFactoryList(AbstractFactories* _factories)=0;
                unsigned int getProductId(){return productId;}
            private:
                unsigned int productId;
        };
        static std::unordered_map<std::string, ProductType*>& productTypeList()
        {
            static std::unordered_map<std::string, ProductType*> list;
            return list;
        }
        template <typename Product>
        class DerivedProductType: public ProductType
        {
            public:
                DerivedProductType(unsigned int& _productId, std::unordered_map<std::string, class ProductType*>* _productTypeList);
                AbstractFactoryListBase* createFactoryList(AbstractFactories* _factories);
        };
        static std::vector<ProductType*> productTypes;
        static unsigned int& newProductIds()
        {
            static unsigned int productId = 0;
            return productId;
        }
        template <typename Product>
        static ProductType* getProductType()
        {
            static DerivedProductType<Product> productType(newProductIds(), &productTypeList());
            return &productType;
        }
        template <typename Product>
        AbstractFactoryList<Product>* getFactoryList()
        {
            ProductType* type = getProductType<Product>();
            AbstractFactoryListBase* factoryList = indexedFactoryLists[type->getProductId()];
            assert(factoryList);
            assert(dynamic_cast<AbstractFactoryList<Product>*>(factoryList));
            return static_cast<AbstractFactoryList<Product>*>(factoryList);
        }
        std::vector<AbstractFactoryListBase*> indexedFactoryLists;
        PhysicsManager* physicsManager;
        CollisionDatabase collisionDatabase;
};

/** Implementation
*
*
*/


#include <AbstractFactory/AbstractFactoryList.h>
#include <AbstractFactory/TypeTableFactoryType.h>
#include <Events/Events/FactoryTypeRegisterEvent.h>
#include <Events/Events.h>
#include <Types/TypeTable.h>

template <typename Product>
Product* AbstractFactories::useFactory(AbstractFactoryReference factory, FactoryParameters* _parameters, GameObjectBase* _parent)
{
    return getFactoryList<Product>()->useFactory(factory,_parameters, _parent);
}
template <typename Product>
AbstractFactoryBase<Product>* AbstractFactories::getFactory(const std::string& name)
{
    return getFactoryList<Product>()->getFactory(name);
}

template <typename Product, typename Factory>
void AbstractFactories::registerFactoryType()
{
    getProductType<Product>();
    auto creator = new TemplateFactoryCreator<Product, Factory>;
    AbstractFactoryList<Product>::registerFactoryType(Factory::name(), creator);
    FactoryTypeRegisterEvent<Product> event(Factory::name());
    Events::global().triggerEvent(&event);
}

template <typename Product>
AbstractFactoryBase<Product>* AbstractFactories::addFactory(FactoryLoader* _loader)
{
    return getFactoryList<Product>()->AbstractFactoryList<Product>::addFactory(this, _loader);
}

template <typename Product>
AbstractFactories::DerivedProductType<Product>::DerivedProductType(unsigned int& _productId, std::unordered_map<std::string, class ProductType*>* _productTypeList)
:ProductType(_productId)
{
    (*_productTypeList)[EvaluateTypeName<Product>()] = this;
    TypeTable::overloadType<AbstractFactoryBase<Product>*>(AbstractFactoryList<Product>::getProductName()+"Factory", new TypeTableFactoryType<Product>);
}

template <typename Product>
AbstractFactoryListBase* AbstractFactories::DerivedProductType<Product>::createFactoryList(AbstractFactories* _factories)
{
    return new AbstractFactoryList<Product>(_factories);
}










#endif // ABSTRACTFACTORIES_H
