#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include <string>
#include <istream>
#include <Graphics/GraphicsManager.h> /// FIXME
#include <Events/Events/EntityDeathEvent.h>
class FactoryParameters;
class FactoryLoader;
template <typename Product>
class AbstractFactoryList;
template <typename DerivedEvent>
class EventsListener;
class AbstractFactories;


template <typename Product>
class AbstractFactoryBase
{
    public:
        AbstractFactoryBase(const std::string _name);
        virtual ~AbstractFactoryBase();
        virtual void baseInit(const std::string& _name, FactoryLoader* loader, AbstractFactories* factories)=0;
        Product* use(FactoryParameters* paramters);
        const std::string& getName(){return nameCache;}
        const std::string& getInstanceName(){return instanceName;}
    protected:
        virtual Product* privateUseFactory(FactoryParameters* parameters)=0;
        const std::string nameCache;
        std::string instanceName;
    private:
};
template <typename Product, typename DerivedType>
class Registrar
{
    public:
        Registrar();
        void check()const{}
};
template <typename Product, typename DerivedType>
class AbstractFactory: public AbstractFactoryBase<Product>
{
    public:
        AbstractFactory();
        ~AbstractFactory();
        void baseInit(const std::string& _name, FactoryLoader* loader, AbstractFactories* factories);
    private:
        Product* privateUseFactory(FactoryParameters* parameters);
        const static Registrar<Product, DerivedType> registrar;

        static EventsListener<DeathEvent<Product>>* factoryTypeDeathListeners;
        EventsListener<DeathEvent<Product>>* factoryNameDeathListeners;
};

/** Implementation
*
*
*/



#include <AbstractFactory/AbstractFactories.h>
#include <Events/Events.h>
#include <Events/Events/FactoryInstanceUsageEvent.h>

template <typename Product>
AbstractFactoryBase<Product>::AbstractFactoryBase(const std::string _name)
:nameCache(_name)
{
    //ctor
}

template <typename Product>
AbstractFactoryBase<Product>::~AbstractFactoryBase()
{
    //dtor
}

template <typename Product>
Product* AbstractFactoryBase<Product>::use(FactoryParameters* parameters)
{
    Product* product = privateUseFactory(parameters);
    FactoryUsageEvent<Product> untypedEvent(product);
    Events::global().triggerEvent(&untypedEvent);
    return product;
}
template <typename Product, typename DerivedType>
AbstractFactory<Product, DerivedType>::AbstractFactory()
:AbstractFactoryBase<Product>(DerivedType::name())
{
    registrar.check();
    factoryNameDeathListeners = nullptr;
}
template <typename Product, typename DerivedType>
AbstractFactory<Product, DerivedType>::~AbstractFactory()
{

}
/**
    If the derived factory doesn't override this function it will result in a compile error
**/
template <typename Product, typename DerivedType>
void AbstractFactory<Product, DerivedType>::baseInit(const std::string& _name, FactoryLoader* loader, AbstractFactories* factories)
{
    AbstractFactoryBase<Product>::instanceName = _name;
    static_cast<DerivedType*>(this)->init(loader, factories);
}

template <typename Product, typename DerivedType>
Product* AbstractFactory<Product, DerivedType>::privateUseFactory(FactoryParameters* parameters)
{
    Product* product = static_cast<DerivedType*>(this)->useFactory(parameters);
    FactoryTypeUsageEvent<Product, DerivedType> typeEvent(product);
    Events::global().triggerEvent(&typeEvent);
    FactoryInstanceUsageEvent<Product, DerivedType> instanceEvent(product, "error this is stupid");
    Events::global().triggerEvent(&typeEvent);
    for (auto i = factoryTypeDeathListeners; i != nullptr; i = i->getNext())
    {
        product->registerDeathListener(i);
    }
    for (auto i = factoryNameDeathListeners; i != nullptr; i = i->getNext())
    {
        product->registerDeathListener(i);
    }
    return product;
}

template <typename Product, typename DerivedType>
const Registrar<Product, DerivedType> AbstractFactory<Product, DerivedType>::registrar;
template <typename Product, typename DerivedType>
Registrar<Product, DerivedType>::Registrar()
{
    AbstractFactories::global().registerFactoryType<Product, DerivedType>();
}

template <typename Product, typename DerivedType>
EventsListener<DeathEvent<Product>>* AbstractFactory<Product, DerivedType>::factoryTypeDeathListeners = nullptr;
#endif // ABSTRACTFACTORY_H
