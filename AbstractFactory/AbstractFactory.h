#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include <Box2D/Box2D.h>
#include <string>
#include <istream>
class Entity;
class FactoryParameters;

template <typename Product>
class AbstractFactoryBase
{
    public:
        AbstractFactoryBase();
        virtual ~AbstractFactoryBase();
        virtual Product* useFactory(FactoryParameters* parameters)=0;
    protected:
        void setMaterial(class Skin* skin,const std::string& materialName);
        b2BodyDef bodyDef;
    private:
};
template <typename DerivedType>
class Registrar
{
    public:
        Registrar();
        void check();
};
template <typename Product, typename DerivedType>
class AbstractFactory: public AbstractFactoryBase<Product>
{
    public:
        AbstractFactory();
        ~AbstractFactory();
    private:
        static Registrar<DerivedType> registrar;
        static char registration;
};

#include <AbstractFactory/AbstractFactories.h>
/*template<typename Product, class DerivedType>
AbstractFactory<Product, DerivedType>::Registrar AbstractFactory<Product, DerivedType>::registration = g_AbstractFactories.registerFactoryType<DerivedType>(DerivedType::getName());
*/
#include <Graphics/GraphicsManager.h>

template <typename Product>
AbstractFactoryBase<Product>::AbstractFactoryBase()
{
    //ctor
}

template <typename Product>
AbstractFactoryBase<Product>::~AbstractFactoryBase()
{
    //dtor
}

template <typename Product>
void AbstractFactoryBase<Product>::setMaterial(class Skin* skin,const std::string& materialName)
{
    skin->material = g_GraphicsManager.getMaterial(materialName.c_str());
}

template <typename Product, typename DerivedType>
AbstractFactory<Product, DerivedType>::AbstractFactory()
{
    static Registrar<DerivedType> temp;
}
template <typename Product, typename DerivedType>
AbstractFactory<Product, DerivedType>::~AbstractFactory()
{

}

#include <AbstractFactory/AbstractFactories.h>
#include <iostream>
template <typename DerivedType>
Registrar<DerivedType>::Registrar()
{
    std::cout << DerivedType::name() << " initialisation" << std::endl;
    g_AbstractFactories.registerFactoryType<DerivedType>(DerivedType::name());
}

#endif // ABSTRACTFACTORY_H
