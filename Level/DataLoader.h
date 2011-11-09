#ifndef DATALOADER_H
#define DATALOADER_H

#include <string>
#include <unordered_map>

template <typename DerivedClass, typename Product>
class DataLoader
{
    public:
        DataLoader();
        virtual ~DataLoader();
        Product* load(const std::string& _address);
    protected:
    private:
        std::unordered_map<std::string, Product*> alreadyLoaded;
};

template <typename DerivedClass, typename Product>
DataLoader<DerivedClass, Product>::DataLoader()
{
    //ctor
}

template <typename DerivedClass, typename Product>
DataLoader<DerivedClass, Product>::~DataLoader()
{
    //dtor
}

template <typename DerivedClass, typename Product>
Product* DataLoader<DerivedClass, Product>::load(const std::string& _address)
{
    auto iter = alreadyLoaded.find(_address);
    if (iter == alreadyLoaded.end())
    {
        Product* product = new Product;
        alreadyLoaded[_address] = product;
        static_cast<DerivedClass*>(this)->virtualLoad(_address, product);
        return product;
    }
    else
    {
        Product* product = iter->second;
        product->increment();
        return product;
    }
}
#endif // DATALOADER_H
