#ifndef FACTORYUSAGECOLLECTION_H
#define FACTORYUSAGECOLLECTION_H

#include <unordered_map>
#include <AbstractFactory/FactoryParameters.h>
template <typename Product>
class AbstractFactoryList;

template <typename Product>
class FactoryUsageCollection
{
    public:
        FactoryUsageCollection();
        virtual ~FactoryUsageCollection();
        //void useFactory
    protected:
    private:
        AbstractFactoryList<Product>* factoryList;
        std::unordered_map<Product*, FactoryParameters> productTable;
};

#endif // FACTORYUSAGECOLLECTION_H
