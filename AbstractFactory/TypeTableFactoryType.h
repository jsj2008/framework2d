#ifndef TYPETABLEFACTORYTYPE_H
#define TYPETABLEFACTORYTYPE_H

#include <Types/TypeTable.h>
#include <AbstractFactory/AbstractFactory.h>
template <typename Product>
class AbstractFactoryList;

template <typename Product>
class TypeTableFactoryType : public TypeTable::Type
{
    public:
        TypeTableFactoryType(AbstractFactoryList<Product>* _factoryList);
        virtual ~TypeTableFactoryType();
        TypeTable::Value* instance(const std::string& _value);
        TypeTable::Type* clone();
    protected:
    private:
        AbstractFactoryList<Product>* factoryList;
        class Value : public TypeTable::TemplateBaseValue<AbstractFactoryBase<Entity>*>
        {
            public:
                Value();
                ~Value();
        };
};

#include <AbstractFactory/AbstractFactoryList.h>

template <typename Product>
TypeTableFactoryType<Product>::TypeTableFactoryType(AbstractFactoryList<Product>* _factoryList)
{
    //ctor
    factoryList = _factoryList;
}
template <typename Product>
TypeTableFactoryType<Product>::~TypeTableFactoryType()
{
    //dtor
}

template <typename Product>
TypeTable::Value* TypeTableFactoryType<Product>::instance(const std::string& _value)
{
    TypeTable::TemplateValue<AbstractFactoryBase<Product>*>* value = new TypeTable::TemplateValue<AbstractFactoryBase<Product>*>;
    AbstractFactoryBase<Product>* factory = factoryList->getFactory(_value);
    value->set(factory);
    return value;
}
template <typename Product>
TypeTable::Type* TypeTableFactoryType<Product>::clone()
{
    return new TypeTableFactoryType<Product>(factoryList);
}
#endif // TYPETABLEFACTORYTYPE_H
