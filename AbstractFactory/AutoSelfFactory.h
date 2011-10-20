#ifndef AUTOSELFFACTORY_H
#define AUTOSELFFACTORY_H

#include <AbstractFactory/AbstractFactory.h>

template <typename Product, typename DerivedType>
class AutoSelfFactory : public AbstractFactory<Product, AutoSelfFactory<Product, DerivedType>>
{
    public:
        AutoSelfFactory();
        virtual ~AutoSelfFactory();
        static std::string name()
        {
            return DerivedType::factoryName();
        }
        void init(FactoryLoader* loader, AbstractFactories* factories);
        Product* useFactory(FactoryParameters* parameters);
    protected:
    private:
        typename DerivedType::ImmutableData immutableData;
};


template <typename Product, typename DerivedType>
AutoSelfFactory<Product, DerivedType>::AutoSelfFactory()
{
    //ctor
}

template <typename Product, typename DerivedType>
AutoSelfFactory<Product, DerivedType>::~AutoSelfFactory()
{
    //dtor
}

template <typename Product, typename DerivedType>
void AutoSelfFactory<Product, DerivedType>::init(FactoryLoader* loader, AbstractFactories* factories)
{
    immutableData.init(loader, factories);
}

template <typename Product, typename DerivedType>
Product* AutoSelfFactory<Product, DerivedType>::useFactory(FactoryParameters* parameters)
{
    return new DerivedType(immutableData, parameters);
}
#endif // AUTOSELFFACTORY_H
