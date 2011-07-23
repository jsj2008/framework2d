#ifndef ABSTRACTFACTORYLIST_H
#define ABSTRACTFACTORYLIST_H

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
#include <Events/Events/FactoryEvent.h>
template <typename Product>
const std::string EvaluateTypeName();
class FactoryLoader;

class AbstractFactoryListBase
{
    public:
        AbstractFactoryListBase(std::unordered_map<std::string, AbstractFactoryListBase*>* factoryLists, const std::string& _productName);
        virtual ~AbstractFactoryListBase();
        virtual void init(AbstractFactories* factories)=0;
        virtual void print()=0;
        virtual UntypedAbstractFactory* getUntypedFactory(const std::string& name)=0;
    protected:
    private:
};

template <typename Product>
class AbstractFactoryList: private AbstractFactoryListBase
{
    public:
        AbstractFactoryList(std::unordered_map<std::string, AbstractFactoryListBase*>* factoryLists);
        void init(AbstractFactories* factories);
        virtual ~AbstractFactoryList();

        template <typename Factory>
        void registerFactoryType(const std::string& name, AbstractFactories* factories);

        void addFactory(AbstractFactories* _factories, FactoryLoader* _loader);

        Product* useFactory(AbstractFactoryReference factory, FactoryParameters* parameters = nullptr);
        AbstractFactoryBase<Product>* getFactory(AbstractFactoryReference factory);
        UntypedAbstractFactory* getUntypedFactory(const std::string& name);
        const std::string& getProductName()
        {
            return productName();
        }
        void setProductName(const std::string& _productName)
        {
            productName() = _productName;
        }
        void print();
    protected:
    private:
        std::string& productName()
        {
            static std::string name = EvaluateTypeName<Product>();
            return name;
        }
        std::unordered_map<std::string,FactoryCreator<Product>*> factoryCreators;
        std::unordered_map<AbstractFactoryReference,AbstractFactoryBase<Product>*> factories;
};


/** Implementation
*
*
*/

#include <AbstractFactory/FactoryLoaders/TextFileFactoryLoader.h>
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

template <typename Product>
template <typename Factory>
void AbstractFactoryList<Product>::registerFactoryType(const std::string& name, AbstractFactories* _factories)
{
    auto creator = new TemplateFactoryCreator<Product, Factory>;
    factoryCreators[name] = creator;
    AbstractFactoryBase<Product>* factory = creator->createFactory();
    factories[name] = factory;
}


#include <AbstractFactory/FactoryParameters.h>
#include <AbstractFactory/AbstractFactory.h>
#include <AbstractFactory/UntypedAbstractFactoryImplementation.h>
#include <Events/Events/FactoryGetEvent.h>
#include <Events/Events.h>

template <typename Product>
AbstractFactoryBase<Product>* AbstractFactoryList<Product>::getFactory(AbstractFactoryReference factory)
{
    FactoryGetEvent event(factory);
    Events::global().triggerEvent(&event);
    return factories.find(factory)->second;
}

template <typename Product>
Product* AbstractFactoryList<Product>::useFactory(AbstractFactoryReference factory, FactoryParameters* parameters)
{
    Product* product;
    if (parameters == nullptr)
    {
        static FactoryParameters params;
        assert(factories[factory]);
        product = factories[factory]->use(&params);
    }
    else
    {
        assert(factories[factory]);
        product = factories[factory]->use(parameters);
    }
    return product;
}
template <typename Product>
void AbstractFactoryList<Product>::init(AbstractFactories* _factories)
{
    static TextFileFactoryLoader emptyConfig(nullptr);
    for (auto i = factories.begin(); i != factories.end(); i++)
    {
        i->second->init(&emptyConfig, _factories);
    }
    TextFileFactoryLoader loader(("Resources/" + productName() + "Factories.txt").c_str());
    while (loader.next())
    {
        assert(factories.find(loader.getName()) == factories.end());
        AbstractFactoryBase<Product>* factory = factoryCreators[loader.getType()]->createFactory();
        factory->init(&loader, _factories);
        factories[loader.getName()] = factory;
        loader.end();
    }
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
    AbstractFactoryBase<Product>* factory = factoryCreators[_loader->getType()]->createFactory();
    factory->init(_loader, _factories);
    factories[_loader->getName()] = factory;
}


template <typename Product>
AbstractFactoryList<Product>::AbstractFactoryList(std::unordered_map<std::string, AbstractFactoryListBase*>* factoryLists)
:AbstractFactoryListBase(factoryLists, productName())
{
    //ctor
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
