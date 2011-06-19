#ifndef ABSTRACTFACTORIES_H
#define ABSTRACTFACTORIES_H

#include <string>
typedef std::string AbstractFactoryReference;
template <typename Product>
class AbstractFactoryList;
class Entity;
class FactoryParameters;

class AbstractFactories
{
    public:
        template <typename Product>
        Product* useFactory(AbstractFactoryReference factory, FactoryParameters* parameters = NULL);

        template <typename Product, typename Factory>
        char registerFactoryType(const std::string& name);

        template <typename Product>
        void initFactoryList()
        {
            getFactoryList<Product>().init();
        }

        static AbstractFactories& getSingleton()
        {
            static AbstractFactories factories;
            return factories;
        }
        template <typename Product>
        AbstractFactoryList<Product>& getFactoryList()
        {
            static AbstractFactoryList<Product> factoryList;
            return factoryList;
        }
    protected:
    private:
        AbstractFactories();
        virtual ~AbstractFactories();
        /*template <typename Product>
        AbstractFactoryList<Product>& getFactoryList();*/
};
#define g_AbstractFactories AbstractFactories::getSingleton().getFactoryList<Entity>()
#include <AbstractFactory/AbstractFactoryList.h>

template <typename Product>
Product* AbstractFactories::useFactory(AbstractFactoryReference factory, FactoryParameters* parameters)
{
    return getFactoryList<Product>().useFactory(factory,parameters);
}

template <typename Product, typename Factory>
char AbstractFactories::registerFactoryType(const std::string& name)
{
    AbstractFactoryList<Product> list = getFactoryList<Product>();
    list.registerFactoryType<Factory>(name);
    return 0;
}

#endif // ABSTRACTFACTORIES_H
