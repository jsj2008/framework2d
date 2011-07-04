#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include <string>
#include <istream>
#include <Graphics/GraphicsManager.h> /// FIXME
class FactoryParameters;
class EventHandler;
template <typename Product>
class AbstractFactoryList;
class EventsListener;

template <typename Product>
class AbstractFactoryBase
{
    public:
        AbstractFactoryBase(const std::string _name);
        virtual ~AbstractFactoryBase();
        Product* use(FactoryParameters* paramters);
        const std::string& getName(){return nameCache;}
        void registerListener(EventsListener* listener);
    protected:
        virtual Product* privateUseFactory(FactoryParameters* parameters)=0;
        const std::string nameCache;
        void setMaterial(class Skin* skin,const std::string& materialName);
    private:
        friend class AbstractFactoryList<Product>;
        static EventHandler productTypeEventHandler;
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
    private:
        Product* privateUseFactory(FactoryParameters* parameters);
        const static Registrar<Product, DerivedType> registrar;
        EventHandler* getFactoryTypeEventHandler()
        {
            static EventHandler eventHandler;
            return &eventHandler;
        }
};

/** Implementation
*
*
*/



#include <AbstractFactory/AbstractFactories.h>
#include <Events/EventHandler.h>

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
    FactoryEvent<Product> event(product);
    productTypeEventHandler.trigger(&event);
    return product;
}
template <typename Product>
void AbstractFactoryBase<Product>::registerListener(EventsListener* listener)
{
    productTypeEventHandler.registerListener(listener);
}
template <typename Product>
void AbstractFactoryBase<Product>::setMaterial(class Skin* skin,const std::string& materialName)
{
    skin->material = g_GraphicsManager.getMaterial(materialName.c_str());
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
template <typename Product, typename DerivedType>
Product* AbstractFactory<Product, DerivedType>::privateUseFactory(FactoryParameters* parameters)
{
    Product* product = static_cast<DerivedType*>(this)->useFactory(parameters);
    FactoryEvent<Product> event(product);
    getFactoryTypeEventHandler()->trigger(&event);
    return product;
}

template <typename Product, typename DerivedType>
const Registrar<Product, DerivedType> AbstractFactory<Product, DerivedType>::registrar;
template <typename Product, typename DerivedType>
Registrar<Product, DerivedType>::Registrar()
{
    AbstractFactories::registerFactoryType<Product, DerivedType>();
}
template <typename Product>
EventHandler AbstractFactoryBase<Product>::productTypeEventHandler;

#endif // ABSTRACTFACTORY_H
