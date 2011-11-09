#ifndef ABSTRACTFACTORYLIST_H
#define ABSTRACTFACTORYLIST_H

#include <GameObject.h>
#include <string>
typedef std::string AbstractFactoryReference;
#include <unordered_map>
template <typename Product>
class FactoryCreator;
template <typename Product>
class AbstractFactoryBase;
class FactoryParameters;
class UntypedAbstractFactory;
class AbstractFactories;
template <typename Product>
const std::string EvaluateTypeName();
class FactoryLoader;

class AbstractFactoryListBase : public GameObject<AbstractFactoryListBase>
{
    public:
        AbstractFactoryListBase(){}
        virtual ~AbstractFactoryListBase();
        virtual void print()=0;
        virtual UntypedAbstractFactory* getUntypedFactory(const std::string& name)=0;
        virtual void addFactory(AbstractFactories* _factories, FactoryLoader* _loader)=0;

        static void registerActions();
    protected:
    private:
};

template <typename Product>
class AbstractFactoryList: public AbstractFactoryListBase
{
    public:
        AbstractFactoryList(AbstractFactories* _factoriesListList);
        virtual ~AbstractFactoryList();

        template <typename Factory>
        static void registerFactoryType(const std::string& _name);

        static void registerFactoryType(const std::string& _name, FactoryCreator<Product>* _creator);

        void addFactory(AbstractFactories* _factories, FactoryLoader* _loader);

        Product* useFactory(AbstractFactoryReference factory, FactoryParameters* parameters = nullptr);
        AbstractFactoryBase<Product>* getFactory(AbstractFactoryReference factory);
        UntypedAbstractFactory* getUntypedFactory(const std::string& name);
        static const std::string& getProductName()
        {
            return productName();
        }
        static void setProductName(const std::string& _productName)
        {
            productName() = _productName;
        }
        void print();

    protected:
    private:
        static std::string& productName()
        {
            static std::string name = EvaluateTypeName<Product>();
            return name;
        }
        AbstractFactories* factoriesListList;
        static std::unordered_map<std::string,FactoryCreator<Product>*>& factoryCreators()
        {
            static std::unordered_map<std::string,FactoryCreator<Product>*> list;
            return list;
        }
        std::unordered_map<AbstractFactoryReference,AbstractFactoryBase<Product>*> factories;
};


/** Implementation
*
*
*/

template <typename Product>
class FactoryCreator
{
    public:
        virtual AbstractFactoryBase<Product>* createFactory()=0;
};

template <typename Product, typename Factory>
class TemplateFactoryCreator : public FactoryCreator<Product>
{
    public:
        AbstractFactoryBase<Product>* createFactory(){return new Factory();}
};

#include <AbstractFactory/FactoryLoaders/TextFileFactoryLoader.h>
#include <AbstractFactory/FactoryParameters.h>
#include <AbstractFactory/AbstractFactory.h>
#include <AbstractFactory/UntypedAbstractFactoryImplementation.h>

/*template <typename Product>
template <typename Factory>
void AbstractFactoryList<Product>::registerFactoryType(const std::string& name)
{
    if (factoryCreators.find(name) == factoryCreators.end())
    {
        auto creator = new TemplateFactoryCreator<Product, Factory>;
        factoryCreators[name] = creator;
        FactoryTypeRegisterEvent<Product> event(name);
        Events::global().triggerEvent(&event);
    }
}*/
template <typename Product>
void AbstractFactoryList<Product>::registerFactoryType(const std::string& name, FactoryCreator<Product>* _creator)
{
    if (factoryCreators().find(name) == factoryCreators().end())
    {
        factoryCreators()[name] = _creator;
    }
    else delete _creator;
}


template <typename Product>
AbstractFactoryBase<Product>* AbstractFactoryList<Product>::getFactory(AbstractFactoryReference _factory)
{
    AbstractFactoryBase<Product>* factory = factories[_factory];
    if (factory == nullptr)
    {
        auto creator = factoryCreators().find(_factory);
        if (creator != factoryCreators().end())
        {
            factory = creator->second->createFactory();
            factories[_factory] = factory;
            static TextFileFactoryLoader emptyConfig(nullptr, factoriesListList);
            factory->baseInit(_factory, &emptyConfig, factoriesListList);
            return factory;
        }
        g_Log.error("No such factory: " + _factory);
    }
    return factory;
}

template <typename Product>
Product* AbstractFactoryList<Product>::useFactory(AbstractFactoryReference factory, FactoryParameters* parameters)
{
    Product* product;
    if (parameters == nullptr)
    {
        static FactoryParameters params(nullptr);
        product = getFactory(factory)->use(&params);
    }
    else
    {
        product = getFactory(factory)->use(parameters);
        std::string name = parameters->get<std::string>("name", "");
        if (name != "")
        {
        }
    }
    return product;
}
template <typename Product>
UntypedAbstractFactory* AbstractFactoryList<Product>::getUntypedFactory(const std::string& name)
{
    return new UntypedAbstractFactoryImplementation<Product>(factories[name]);
}

template <typename Product>
void AbstractFactoryList<Product>::addFactory(AbstractFactories* _factories, FactoryLoader* _loader)
{
    assert(factories.find(_loader->getName()) == factories.end());
    AbstractFactoryBase<Product>* factory = factoryCreators()[_loader->getType()]->createFactory();
    attachChild(factory);
    factory->baseInit(_loader->getName(), _loader, _factories);
    factories[_loader->getName()] = factory;
}

#include <AbstractFactory/TypeTableFactoryType.h>
template <typename Product>
AbstractFactoryList<Product>::AbstractFactoryList(AbstractFactories* _factoriesListList)
{
    //ctor
    factoriesListList = _factoriesListList;
}

template <typename Product>
AbstractFactoryList<Product>::~AbstractFactoryList()
{
    //dtor
}

void privatePrint(std::ostream* stream, const std::string& factoryType, const std::string& factoryInstance, const std::string& productName, const std::string& realProductName);
template <typename Product>
void AbstractFactoryList<Product>::print()
{
    std::ofstream file("Resources/" + productName() + "Factories.txt");
    for (auto i = factories.begin(); i != factories.end(); i++)
    {
        privatePrint(&file, i->second->getName(), i->first, productName(), EvaluateTypeName<Product>());
    }
}
#include <AbstractFactory/EvaluateTypeName.h>

#endif // ABSTRACTFACTORYLIST_H
