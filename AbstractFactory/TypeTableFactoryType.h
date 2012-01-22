#ifndef TYPETABLEFACTORYTYPE_H
#define TYPETABLEFACTORYTYPE_H

#include <Types/TypeTable.h>
#include <AbstractFactory/AbstractFactory.h>
template <typename Product>
class AbstractFactoryList;

template <typename Product>
class TypeTableFactoryType : public TypeTable::TemplateBaseType<AbstractFactoryBase<Product>*>
{
    public:
        TypeTableFactoryType(); /// FIXME want to use this class, but without the back pointer because its for statics
        virtual ~TypeTableFactoryType();
        TypeTable::Value* parseInstance(TypeTable* _typeTable, const std::string& _value);
        TypeTable::ArrayValue* arrayInstance(){throw -1;} /// Don't see why you'd want an array of Factories atm
        TypeTable::Value* instance(AbstractFactoryBase<Product>* _value);
        TypeTable::Type* clone();
    protected:
    private:
        class Value : public TypeTable::TemplateBaseValue<AbstractFactoryBase<Product>*>
        {
            public:
                Value();
                ~Value();
                void output(std::ostream* _stream);
                void output(PropertyBagSerializer* _out);
                TypeTable::Value* clone();
                std::string getTypeId();
        };
};

#include <AbstractFactory/AbstractFactoryList.h>

template <typename Product>
TypeTableFactoryType<Product>::TypeTableFactoryType()
{
    //ctor
}
template <typename Product>
TypeTableFactoryType<Product>::~TypeTableFactoryType()
{
    //dtor
}

template <typename Product>
TypeTable::Value* TypeTableFactoryType<Product>::parseInstance(TypeTable* _table, const std::string& _value)
{
    TypeTable::TemplateBaseValue<AbstractFactoryBase<Product>*>* value = new Value;
    AbstractFactoryBase<Product>* factory = _table->getFactories()->getFactory<Product>(_value);
    value->set(factory);
    return value;
}
template <typename Product>
TypeTable::Value* TypeTableFactoryType<Product>::instance(AbstractFactoryBase<Product>* _value)
{
    Value* value = new Value;
    value->set(_value);
    return value;
}
template <typename Product>
TypeTable::Type* TypeTableFactoryType<Product>::clone()
{
    return new TypeTableFactoryType<Product>;
}
template <typename Product>
TypeTableFactoryType<Product>::Value::Value()
{

}

template <typename Product>
TypeTableFactoryType<Product>::Value::~Value()
{

}

template <typename Product>
void TypeTableFactoryType<Product>::Value::output(std::ostream* _stream)
{
    *_stream << TypeTable::TemplateBaseValue<AbstractFactoryBase<Product>*>::value->getObjectName();
}
template <typename Product>
void TypeTableFactoryType<Product>::Value::output(PropertyBagSerializer* _out)
{
    _out->outputValue<std::string>(TypeTable::TemplateBaseValue<AbstractFactoryBase<Product>*>::value->getObjectName());
}
template <typename Product>
std::string TypeTableFactoryType<Product>::Value::getTypeId()
{
    return name<Product>() + "Factory";
}

template <typename Product>
TypeTable::Value* TypeTableFactoryType<Product>::Value::clone()
{
    auto ret = new Value;
    ret->set(TypeTable::TemplateBaseValue<AbstractFactoryBase<Product>*>::value);
    return ret;
}

#endif // TYPETABLEFACTORYTYPE_H
