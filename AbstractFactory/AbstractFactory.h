#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include <string>
#include <istream>
#include <GameObject.h>
#include <Events/InstanceEvents/Events/DeathEvent.h>
class FactoryParameters;
class FactoryLoader;
template <typename Product>
class AbstractFactoryList;
template <typename DerivedEvent>
class EventsListener;
class AbstractFactories;


template <typename Product>
class AbstractFactoryBase : public GameObject<AbstractFactoryBase<Product>>
{
    public:
        AbstractFactoryBase(const std::string _name);
        virtual ~AbstractFactoryBase();
        virtual void baseInit(const std::string& _name, FactoryLoader* loader, AbstractFactories* factories)=0;
        Product* use(FactoryParameters* paramters);
        const std::string& getName(){return nameCache;}
        const std::string& getInstanceName(){return instanceName;}
        static void registerActions();
    protected:
        virtual Product* privateUseFactory(FactoryParameters* parameters)=0;
        const std::string nameCache;
        std::string instanceName;
        void attachChild(void* _doNothing){}
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
        static void staticInstantiate(){registrar.check();}
    private:
        Product* privateUseFactory(FactoryParameters* parameters);
        const static Registrar<Product, DerivedType> registrar;
};

/** Implementation
*
*
*/



#include <AbstractFactory/AbstractFactories.h>

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
    attachChild(product);
    return product;
}
template <typename Product>
void AbstractFactoryBase<Product>::registerActions()
{
}

template <typename Product, typename DerivedType>
AbstractFactory<Product, DerivedType>::AbstractFactory()
:AbstractFactoryBase<Product>(DerivedType::name())
{
    registrar.check();
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
    return product;
}

template <typename Product, typename DerivedType>
const Registrar<Product, DerivedType> AbstractFactory<Product, DerivedType>::registrar;
template <typename Product, typename DerivedType>
Registrar<Product, DerivedType>::Registrar()
{
    AbstractFactories::registerFactoryType<Product, DerivedType>();
}

#endif // ABSTRACTFACTORY_H
