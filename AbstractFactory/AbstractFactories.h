#ifndef ABSTRACTFACTORIES_H
#define ABSTRACTFACTORIES_H

#include <string>
#include <vector>
#include <unordered_map>
typedef std::string AbstractFactoryReference;
template <typename Product>
class AbstractFactoryList;
template <typename Product>
class AbstractFactoryBase;
class FactoryParameters;
class UntypedAbstractFactory;
class EventsListener;

class AbstractFactories
{
    public:
        template <typename Product>
        static Product* useFactory(AbstractFactoryReference factory, FactoryParameters* parameters = nullptr);

        template <typename Product, typename Factory>
        static void registerFactoryType();

        template <typename Product>
        static void renameProduct(const std::string& name);

        template <typename Product>
        static AbstractFactoryBase<Product>* getFactory(const std::string& name);

        /// For this function, considering storing all untyped factories in one list refernced by one parameter,
        /// if I start to use it enough. These are inefficient to create and use, but it will take a little more
        /// time and memory to maintain a list of all factories
        static UntypedAbstractFactory* getUntypedFactory(const std::string& type, const std::string& name);

        static void init();

        static void print(std::ostream* stream);

        template <typename Product>
        static void registerListener(EventsListener* listener){getFactoryList<Product>()->registerListener(listener);}

    protected:
    private:
        template <typename Product>
        static AbstractFactoryList<Product>* getFactoryList()
        {
            static AbstractFactoryList<Product> factoryList(getFactoryListList());
            return &factoryList;
        }
        AbstractFactories();
        ~AbstractFactories();
        static std::unordered_map<std::string, class AbstractFactoryListBase*>* getFactoryListList()
        {
            static std::unordered_map<std::string, class AbstractFactoryListBase*> factoryLists;
            return &factoryLists;
        }
};

/** Implementation
*
*
*/


#include <AbstractFactory/AbstractFactoryList.h>

template <typename Product>
Product* AbstractFactories::useFactory(AbstractFactoryReference factory, FactoryParameters* parameters)
{
    return getFactoryList<Product>()->useFactory(factory,parameters);
}
template <typename Product>
AbstractFactoryBase<Product>* AbstractFactories::getFactory(const std::string& name)
{
    return getFactoryList<Product>()->getFactory(name);
}

template <typename Product, typename Factory>
void AbstractFactories::registerFactoryType()
{
    getFactoryList<Product>()->registerFactoryType<Factory>(Factory::name());
}
template <typename Product>
void AbstractFactories::renameProduct(const std::string& name)
{
    AbstractFactoryList<Product>* list = getFactoryList<Product>();
    (*getFactoryListList())[name] = list;
    getFactoryListList()->erase(list->getProductName());
    list->setProductName(name);
}

#endif // ABSTRACTFACTORIES_H