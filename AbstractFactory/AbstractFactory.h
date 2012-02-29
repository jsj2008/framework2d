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
        Product* use(FactoryParameters* paramters, GameObjectBase* _parent);
        static void registerActions(GameObjectType* _type);
        static std::string name()
        {
            return Product::name() + "Factory";
        }
    protected:
        virtual Product* privateUseFactory(FactoryParameters* _parameters, GameObjectBase* _parent)=0;
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
        Product* privateUseFactory(FactoryParameters* _parameters, GameObjectBase* _parent);
        const static Registrar<Product, DerivedType> registrar;
};

/** Implementation
*
*
*/



#include <AbstractFactory/AbstractFactories.h>

template <typename Product>
AbstractFactoryBase<Product>::AbstractFactoryBase(const std::string _name)
:GameObject<AbstractFactoryBase<Product>>(_name)
{
    //ctor
}

template <typename Product>
AbstractFactoryBase<Product>::~AbstractFactoryBase()
{
    //dtor
}

template <typename Product>
Product* AbstractFactoryBase<Product>::use(FactoryParameters* _parameters, GameObjectBase* _parent)
{
    Product* product = privateUseFactory(_parameters, _parent);
    return product;
}
template <typename Product>
void AbstractFactoryBase<Product>::registerActions(GameObjectType* _type)
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
  GameObjectBase::setObjectName(_name);
    static_cast<DerivedType*>(this)->init(loader, factories);
}

template <typename Product, typename DerivedType>
Product* AbstractFactory<Product, DerivedType>::privateUseFactory(FactoryParameters* _parameters, GameObjectBase* _parent)
{
    Product* product = static_cast<DerivedType*>(this)->useFactory(_parameters);
    if (_parent != nullptr)
        _parent->attachChild(product);
    else
        attachChild(product);
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
