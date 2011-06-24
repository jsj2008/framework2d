#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include <string>
#include <istream>
class FactoryParameters;

template <typename Product>
class AbstractFactoryBase
{
    public:
        AbstractFactoryBase(const std::string* const _name);
        virtual ~AbstractFactoryBase();
        Product* use(FactoryParameters* paramters);
    protected:
        virtual Product* useFactory(FactoryParameters* parameters)=0;
        const std::string* const name;
        void setMaterial(class Skin* skin,const std::string& materialName);
    private:
};
template <typename Product, typename DerivedType>
class Registrar
{
    public:
        Registrar();
        void check(){}
};
template <typename Product, typename DerivedType>
class AbstractFactory: public AbstractFactoryBase<Product>
{
    public:
        AbstractFactory();
        ~AbstractFactory();
    private:
        const static Registrar<Product, DerivedType> registrar;
};

#include <AbstractFactory/AbstractFactories.h>
/*template<typename Product, class DerivedType>
AbstractFactory<Product, DerivedType>::Registrar AbstractFactory<Product, DerivedType>::registration = g_AbstractFactories.registerFactoryType<DerivedType>(DerivedType::getName());
*/
#include <Graphics/GraphicsManager.h>

template <typename Product>
AbstractFactoryBase<Product>::AbstractFactoryBase(const std::string* const _name)
:name(_name)
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
    return useFactory(parameters);
}

template <typename Product>
void AbstractFactoryBase<Product>::setMaterial(class Skin* skin,const std::string& materialName)
{
    skin->material = g_GraphicsManager.getMaterial(materialName.c_str());
}

template <typename Product, typename DerivedType>
AbstractFactory<Product, DerivedType>::AbstractFactory()
:AbstractFactoryBase<Product>(&DerivedType::name())
{
    registrar.check();
}
template <typename Product, typename DerivedType>
AbstractFactory<Product, DerivedType>::~AbstractFactory()
{

}

template <typename Product, typename DerivedType>
const Registrar<Product, DerivedType> AbstractFactory<Product, DerivedType>::registrar;
#include <AbstractFactory/AbstractFactories.h>
#include <iostream>
template <typename Product, typename DerivedType>
Registrar<Product, DerivedType>::Registrar()
{
    AbstractFactories::registerFactoryType<Product, DerivedType>();
}

#endif // ABSTRACTFACTORY_H
