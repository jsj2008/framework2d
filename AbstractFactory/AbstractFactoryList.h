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

template <typename Product>
class AbstractFactoryList
{
    public:
        AbstractFactoryList();
        void init();
        virtual ~AbstractFactoryList();
        template <typename Factory>
        void registerFactoryType(const std::string& name);
        Product* useFactory(AbstractFactoryReference factory, FactoryParameters* parameters = NULL);
    protected:
    private:
        std::unordered_map<std::string,FactoryCreator<Product>*> factoryCreators;
        std::unordered_map<AbstractFactoryReference,AbstractFactoryBase<Product>*> factories;
};

#include <AbstractFactory/FactoryParameters.h>
#include <AbstractFactory/AbstractFactory.h>
#include <AbstractFactory/FactoryLoader.h>

template <typename Product>
Product* AbstractFactoryList<Product>::useFactory(AbstractFactoryReference factory, FactoryParameters* parameters)
{
    if (parameters == NULL)
    {
        static FactoryParameters params;
        //params.clear();
        return factories[factory]->useFactory(&params);
    }
    return factories[factory]->useFactory(parameters);
}
class FactoryLoader;
template <typename Product>
class FactoryCreator
{
    public:
        virtual AbstractFactoryBase<Product>* createFactory(FactoryLoader* loader)=0;
};

template <typename Product, typename Factory>
class TemplateFactoryCreator : public FactoryCreator<Product>
{
    public:
        AbstractFactoryBase<Product>* createFactory(FactoryLoader* loader){return new Factory(loader);}
};

template <typename Product>
template <typename Factory>
void AbstractFactoryList<Product>::registerFactoryType(const std::string& name)
{
    factoryCreators[name] = new TemplateFactoryCreator<Product, Factory>;
}
template <typename Product>
void AbstractFactoryList<Product>::init()
{
    FactoryLoader loader("Resources/Factories.txt");
    while (loader.next())
    {
        assert(factories.find(loader.getName()) == factories.end());
        factories[loader.getName()] = factoryCreators[loader.getType()]->createFactory(&loader);
        loader.end();
    }
}
#endif // ABSTRACTFACTORYLIST_H
