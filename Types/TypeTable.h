#ifndef TYPETABLE_H
#define TYPETABLE_H

#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <cassert>
#include <Types/Vec2f.h>
#include <Log/Log.h>
#include <AbstractFactory/EvaluateTypeName.h>
class AbstractFactories;

template <typename T>
std::string& name()
{
    static std::string name = EvaluateTypeName<T>();
    return name;
}
class PropertyBagSerializer;

class TypeTable
{
    public:
        class Value;
        class ArrayValue;
        typedef std::string ValueIndex;
        typedef std::string TypeIndex;

        TypeTable(AbstractFactories* _factories, bool logUndefined);
        TypeTable(const TypeTable& _rhs);
        virtual ~TypeTable();

    template <typename T>
        void addValue(const ValueIndex& name, const T& value);

    template <typename T>
        void addArray(const ValueIndex& name, const std::vector<T>& value);

    template <typename T>
        void setValue(const ValueIndex& name, const T& value);

    template <typename T>
        const T& getValue(const ValueIndex& name);

    template <typename T>
        const T& getValue(const ValueIndex& name, const T& _default);

    template <typename T>
        const std::vector<T>& getArray(const ValueIndex& name, const std::vector<T>& _default);

    template <typename T>
        const T popValue(const ValueIndex& name, const T& _default);

    template <typename T>
        const T popValue(const ValueIndex& name);

    template <typename T>
        const T popValue(const ValueIndex& name, const char* _default);

        std::unordered_map<ValueIndex,Value*>::iterator begin();
        std::unordered_map<ValueIndex,Value*>::iterator end();

        std::vector<std::string> getUndefinedLog();

        // Don't use these unless neccessary, use the functions in the base class unless you're reading from file or something
        Value* addDynamicValue(const TypeIndex& type, const ValueIndex& name, const std::string& _value);
        ArrayValue* addDynamicArrayValue(const TypeIndex& type, const ValueIndex& name, int _size, const std::string* _values);
        ArrayValue* addDynamicArrayValue(const TypeIndex& type, const ValueIndex& name, int _size, std::istream* parseSource);
        void addDynamicValue(const TypeIndex& type, const ValueIndex& name, std::istream* parseSource);

        void removeValue(const ValueIndex& name);
        void clear();

        void output(std::ostream *out);
        void output(PropertyBagSerializer* _out);
        friend std::ostream& operator<< (std::ostream &out, const TypeTable &table);
        friend std::istream& operator>> (std::istream &in, TypeTable &table);


        class Type
        {
            public:
                Type(){}
                virtual ~Type(){}
                virtual Value* parseInstance(TypeTable* _typeTable, const std::string& _value)=0;
                virtual ArrayValue* arrayInstance()=0;
                virtual Type* clone()=0;
        };
        class Value
        {
            public:
                virtual ~Value(){}
                virtual void output(PropertyBagSerializer* _out)=0;
                virtual void output(std::ostream* parseDestination)=0;
                virtual std::string getTypeId()=0;
                virtual Value* clone()=0;
        };
        template <typename T>
        class TemplateBaseValue : public Value
        {
            public:
                TemplateBaseValue(){}
                TemplateBaseValue(const std::string& _value);
                void set(const T& _value){value = _value;}
                const T& get(){return value;}
            protected:
                T value;
        };
        class ArrayValue : public Value
        {
            public:
                ArrayValue(){}
                virtual void pushValue(const std::string& _value)=0;
                virtual void pushValue(std::istream* _parseSource)=0;
        };
        template <typename T>
        class TemplateBaseArrayValue : public ArrayValue
        {
            public:
                TemplateBaseArrayValue(){}
                const std::vector<T>& get(){return values;}
                void set(const std::vector<T>& _values){values = _values;}
            protected:
                std::vector<T> values;
        };
        template <typename T>
        class TemplateBaseType : public Type
        {
            public:
                virtual Value* instance(T _value)=0;
                virtual ArrayValue* arrayInstance()=0;
        };

        AbstractFactories* getFactories(){return factories;}
        void setFactories(AbstractFactories* _factories){factories = _factories;}

    template <typename T>
        static void overloadType(const TypeIndex& name, Type* _newFactory);

        bool loggingUndefined(){return logUndefined;}
    protected:
        std::unordered_map<ValueIndex,Value*> values;

        class UntypedValue : public Value
        {
            public:
                UntypedValue(TypeIndex _type, const ValueIndex& _name);
                ~UntypedValue();
                void set(std::istream* parseSource); /// FIXME make this something more generic, when I figure out the input type
                void output(std::ostream* parseDestination);
                void output(PropertyBagSerializer* _out){}
                std::string getTypeId();
                Value* clone();
                UntypedValue* typedClone();
                template <typename T>
                Value* instance();
                std::string getValueIndex(){return name;}
            private:
                std::string unparsedValue;
                ValueIndex name;
                TypeIndex type;
        };
        template <typename T>
        class AutomaticRegister
        {
            public:
                AutomaticRegister();
                void check();
        };
        template <typename T>
        class TemplateType : public TemplateBaseType<T>
        {
            public:
                TemplateType(){staticRegister.check();}
                Value* parseInstance(TypeTable* _typeTable, const std::string& _value){return new TemplateValue<T>(_value);}
                ArrayValue* arrayInstance(){return new TemplateArrayValue<T>();}
                Value* instance(T _value){TemplateValue<T>* ret = new TemplateValue<T>; ret->set(_value); return ret;}
                Type* clone(){return new TemplateType<T>();}
            private:
                static AutomaticRegister<T> staticRegister;
        };
        template <typename T>
        class TemplateValue : public TypeTable::TemplateBaseValue<T>
        {
            public:
                TemplateValue(){}
                TemplateValue(const std::string& _value);
                void output(std::ostream* parseDestination){(*parseDestination) << TemplateBaseValue<T>::value;}
                void output(PropertyBagSerializer* _out);
                Value* clone(){TemplateValue<T>* ret = new TemplateValue<T>();ret->set(TemplateBaseValue<T>::value);return ret;}
                std::string getTypeId(){return name<T>();}
            protected:
        };
        template <typename T>
        class TemplateArrayValue : public TypeTable::TemplateBaseArrayValue<T>
        {
            public:
                TemplateArrayValue(){}
                void output(std::ostream* parseDestination);
                void output(PropertyBagSerializer* _out);
                Value* clone(){TemplateArrayValue<T>* ret = new TemplateArrayValue<T>();ret->set(TemplateBaseArrayValue<T>::values);return ret;}
                std::string getTypeId(){return name<T>() + "Array";}
                void set(const std::vector<T>& _values){TemplateBaseArrayValue<T>::values = _values;}
                void pushValue(const std::string& _value);
                void pushValue(std::istream* _parseSource);
                const std::vector<T>& get(){return values;}
            protected:
        };

        static std::unordered_map<TypeIndex,Type*>& types()
        {
            static std::unordered_map<TypeIndex,Type*> _types;
            return _types;
        }
        std::unordered_map<TypeIndex, std::vector<UntypedValue*>> untypedValues;
        bool logUndefined;
        std::unordered_map<ValueIndex, Value*> undefinedLog;
        AbstractFactories* factories;
    private:
    template <typename T>
        void registerType(const TypeIndex& name);
};

#include <Types/PropertyBagSerializer.h>
template <typename T>
void TypeTable::TemplateValue<T>::output(PropertyBagSerializer* _out)
{
    _out->outputValue<T>(TemplateBaseValue<T>::value);
}
template <typename T>
void TypeTable::TemplateArrayValue<T>::output(PropertyBagSerializer* _out)
{
    _out->outputArray<T>(&TemplateBaseArrayValue<T>::values[0], TemplateBaseArrayValue<T>::values.size());
}
template <typename T>
void TypeTable::TemplateArrayValue<T>::output(std::ostream* parseDestination)
{
    *parseDestination << "{ ";
    for (unsigned int i = 0; i < TemplateBaseArrayValue<T>::values.size(); i++)
    {
        *parseDestination << TemplateBaseArrayValue<T>::values[i];
    }
    *parseDestination << '}';
}

template <typename T>
void TypeTable::addValue(const ValueIndex& _name, const T& _value)
{
    auto iter = values.find(_name);
    if(iter != values.end())
    {
        static_cast<TemplateValue<T>*>(iter->second)->set(_value);
    }
    else
    {
        Type* uncastType = types()[name<T>()];
        if (uncastType == nullptr)
        {
            TemplateType<T> type;
            Value* value = type.instance(_value);
            values[_name] = value;
        }
        else
        {
            assert(dynamic_cast<TemplateBaseType<T>*>(uncastType));
            Value* value = static_cast<TemplateBaseType<T>*>(uncastType)->instance(_value);

            values[_name] = value;
        }
    }
}
template <typename T>
void TypeTable::addArray(const ValueIndex& _name, const std::vector<T>& _values)
{
    auto iter = values.find(_name);
    if(iter != values.end())
    {
        static_cast<TemplateBaseArrayValue<T>*>(iter->second)->set(_values);
    }
    else
    {
        TemplateArrayValue<T>* value = new TemplateArrayValue<T>;
        value->set(_values);
        values[_name] = value;
    }
}

template <typename T>
void TypeTable::setValue(const ValueIndex& name, const T& _value)
{
    assert(values.find(name) != values.end());
    Value* value = values[name];
    assert(dynamic_cast<TemplateBaseValue<T>*>(value));
    TemplateBaseValue<T>* typedValue = (TemplateBaseValue<T>*)value;
    typedValue->set(_value);
}

template <typename T>
const T& TypeTable::getValue(const ValueIndex& name)
{
    assert(values.find(name) != values.end());
    Value* value = values[name];
    assert(dynamic_cast<TemplateBaseValue<T>*>(value));
    TemplateBaseValue<T>* typedValue = static_cast<TemplateBaseValue<T>*>(value);
    return typedValue->get();
}

template <typename T>
const T& TypeTable::getValue(const ValueIndex& _name, const T& _default)
{
    auto iter = values.find(_name);
    if (iter == values.end())
    {
        if (logUndefined)
        {
            if (undefinedLog.find(_name) == undefinedLog.end())
            {
                TemplateValue<T>* value = new TemplateValue<T>();
                value->set(_default);
                undefinedLog[_name] = value;
            }
        }
        return _default;
    }
    Value* value = iter->second;
    assert(dynamic_cast<TemplateBaseValue<T>*>(value));
    TemplateBaseValue<T>* typedValue = static_cast<TemplateBaseValue<T>*>(value);
    return typedValue->get();
}
template <typename T>
const std::vector<T>& TypeTable::getArray(const ValueIndex& _name, const std::vector<T>& _default)
{
    auto iter = values.find(_name);
    if (iter == values.end())
    {
        if (logUndefined)
        {
            if (undefinedLog.find(_name) == undefinedLog.end())
            {
                TemplateArrayValue<T>* value = new TemplateArrayValue<T>();
                value->set(_default);
                undefinedLog[_name] = value;
            }
        }
        return _default;
    }
    Value* value = iter->second;
    assert(dynamic_cast<TemplateBaseArrayValue<T>*>(value));
    TemplateBaseArrayValue<T>* typedValue = static_cast<TemplateBaseArrayValue<T>*>(value);
    return typedValue->get();
}

template <typename T>
std::istream& operator>> (std::istream &in, T*& elements)
{
    throw -1;
    elements = nullptr;
    return in;
}

template <typename T>
TypeTable::TemplateValue<T>::TemplateValue(const std::string& _value)
{
    try
    {
        std::stringstream stream(_value);
        stream >> TemplateBaseValue<T>::value;
    }
    catch (...)
    {
        throw this;
    }
}

template <typename T>
const T TypeTable::popValue(const ValueIndex& _name, const T& _default)
{
    try
    {
        return popValue<T>(_name);
    }
    catch (int i)
    {
        if (logUndefined)
            static_cast<TemplateBaseValue<T>*>(undefinedLog[_name])->set(_default);
        return _default;
    }
}
template <typename T>
void TypeTable::TemplateArrayValue<T>::pushValue(const std::string& _value)
{
    T value;
    std::stringstream stream(_value);
    stream >> value;
    TemplateBaseArrayValue<T>::values.push_back(value);
}
template <typename T>
void TypeTable::TemplateArrayValue<T>::pushValue(std::istream* _parseSource)
{
    T value;
    *_parseSource >> value;
    TemplateBaseArrayValue<T>::values.push_back(value);
}
template <typename T>
const T TypeTable::popValue(const ValueIndex& _name)
{
    return popValue<T>(_name, "");
}
template <typename T>
const T TypeTable::popValue(const ValueIndex& _name, const char* _default)
{
    if (values.find(_name) == values.end())
    {
        if (logUndefined)
        {
            if (undefinedLog.find(_name) == undefinedLog.end())
            {
                try
                {
                    TemplateValue<T>* value = static_cast<TemplateValue<T>*>(types()[name<T>()]->parseInstance(this, _default));
                    undefinedLog[_name] = value;
                    return value->get();
                }
                catch (TemplateValue<T>* value)
                {
                    undefinedLog[_name] = value;
                    throw -1;
                }
            }
        }
        throw -1;
    }
    Value* value = values[_name];
    assert(dynamic_cast<TemplateBaseValue<T>*>(value));
    TemplateBaseValue<T>* typedValue = (TemplateBaseValue<T>*)value;
    T ret = typedValue->get();
    delete typedValue;
    values.erase(_name);
    return ret;
}
template <typename T>
std::ostream& operator<< (std::ostream &out, const std::vector<T> &elements)
{
    unsigned short size = elements.size();
    out << size << ' ';
    for (unsigned short i = 0; i < size; i++)
    {
        T element = elements[i];
        out << element << ' ';
    }
    return out;
}
template <typename T>
std::istream& operator>> (std::istream &in, std::vector<T> &elements)
{
    unsigned short size;
    in >> size;
    elements.reserve(size);
    for (unsigned short i = 0; i < size; i++)
    {
        T element;
        in >> element;
        elements.push_back(element);
    }
    return in;
}
template <typename T>
void TypeTable::overloadType(const TypeIndex& _name, Type* _newFactory)
{
    types()[_name] = _newFactory;
    name<T>() = _name;
}
template <typename T>
TypeTable::AutomaticRegister<T>::AutomaticRegister()
{
    delete types()[name<T>()];
    types()[name<T>()] = new TemplateType<T>();
}
template <typename T>
void TypeTable::AutomaticRegister<T>::check()
{
}
template <typename T>
TypeTable::AutomaticRegister<T> TypeTable::TemplateType<T>::staticRegister;
#endif // TYPETABLE_H
