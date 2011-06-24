#ifndef ABSTRACTFACTORIES_H
#define ABSTRACTFACTORIES_H

#include <string>
#include <vector>
#include <unordered_map>
typedef std::string AbstractFactoryReference;
template <typename Product>
class AbstractFactoryList;
class FactoryParameters;

class AbstractFactories
{
    public:
        template <typename Product>
        static Product* useFactory(AbstractFactoryReference factory, FactoryParameters* parameters = NULL);

        template <typename Product, typename Factory>
        static void registerFactoryType();

        template <typename Product>
        static void nameProduct(const std::string& name);

        template <typename Product>
        static void init();
        static void init();
    protected:
    private:
        template <typename Product>
        static AbstractFactoryList<Product>& getFactoryList()
        {
            static AbstractFactoryList<Product> factoryList(getFactoryListList());
            return factoryList;
        }
        AbstractFactories();
        ~AbstractFactories();
        static std::unordered_map<std::string, class AbstractFactoryListBase*>* getFactoryListList()
        {
            static std::unordered_map<std::string, class AbstractFactoryListBase*> factoryLists;
            return &factoryLists;
        }
};
#define g_AbstractFactories AbstractFactories::getFactoryList<Entity>()
#include <AbstractFactory/AbstractFactoryList.h>

template <typename Product>
void AbstractFactories::init()
{
    getFactoryList<Product>().init();
}

template <typename Product>
Product* AbstractFactories::useFactory(AbstractFactoryReference factory, FactoryParameters* parameters)
{
    return getFactoryList<Product>().useFactory(factory,parameters);
}

template <typename Product, typename Factory>
void AbstractFactories::registerFactoryType()
{
    getFactoryList<Product>().registerFactoryType<Factory>(Factory::name());
}
template <typename Product>
void AbstractFactories::nameProduct(const std::string& name)
{
    (*getFactoryListList())[name] = &getFactoryList<Product>();
}

#endif // ABSTRACTFACTORIES_H
