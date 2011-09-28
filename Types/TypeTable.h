#ifndef TYPETABLE_H
#define TYPETABLE_H

#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <Types/Vec2f.h>
#include <Log/Log.h>
#include <AbstractFactory/EvaluateTypeName.h>

template <typename T>
std::string& name()
{
    static std::string name = EvaluateTypeName<T>();
    return name;
}

class TypeTable
{
    public:
        class Value;
        typedef std::string ValueIndex;
        typedef std::string TypeIndex;

        TypeTable(bool logUndefined);
        TypeTable(const TypeTable& _rhs);
        //TypeTable(const TypeTable& rhs);
        virtual ~TypeTable();

    template <typename T>
        void addValue(const ValueIndex& name, const T& value);

    template <typename T>
        void setValue(const ValueIndex& name, const T& value);

    template <typename T>
        const T& getValue(const ValueIndex& name);

    template <typename T>
        const T& getValue(const ValueIndex& name, const T& _default);

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
        void addDynamicValue(const TypeIndex& type, const ValueIndex& name, std::istream* parseSource);

        void removeValue(const ValueIndex& name);
        void clear();

        void output(std::ostream *out);
        friend std::ostream& operator<< (std::ostream &out, const TypeTable &table);
        friend std::istream& operator>> (std::istream &in, TypeTable &table);


        class Type
        {
            public:
                Type(){}
                virtual ~Type(){}
                virtual Value* instance(const std::string& _value)=0;
                virtual Type* clone()=0;
        };
        class Value
        {
            public:
                virtual ~Value(){}
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
        template <typename T>
        class TemplateBaseType : public Type
        {
            public:
                virtual Value* instance(T _value)=0;
        };

    template <typename T>
        static void overloadType(const TypeIndex& name, Type* _newFactory);

    protected:
        std::unordered_map<ValueIndex,Value*> values;

        class UntypedValue : public Value
        {
            public:
                UntypedValue(TypeIndex _type, const ValueIndex& _name);
                ~UntypedValue();
                void set(std::istream* parseSource); /// FIXME make this something more generic, when I figure out the input type
                void output(std::ostream* parseDestination);
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
                Value* instance(const std::string& _value){return new TemplateValue<T>(_value);}
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
                Value* clone(){TemplateValue<T>* ret = new TemplateValue<T>();ret->set(TemplateBaseValue<T>::value);return ret;}
                std::string getTypeId(){return name<T>();}
            protected:
        };

        static std::unordered_map<TypeIndex,Type*> types;
        std::unordered_map<TypeIndex, std::vector<UntypedValue*>> untypedValues;
        bool logUndefined;
        std::unordered_map<ValueIndex, Value*> undefinedLog;
    private:
    template <typename T>
        void registerType(const TypeIndex& name);
};

template <typename T>
std::istream& operator>> (std::istream &in, std::vector<T> &elements);
template <typename T>
std::ostream& operator<< (std::ostream &out, const std::vector<T> &elements);

template <typename T>
void TypeTable::addValue(const ValueIndex& _name, const T& _value)
{
    if(values.find(_name) != values.end())
    {
        delete values[_name];
    }
    Type* uncastType = types[name<T>()];
    assert(dynamic_cast<TemplateBaseType<T>*>(uncastType));
    TemplateValue<T>* value = static_cast<TemplateBaseType<T>*>(uncastType)->instance(_value);
    values[_name] = value;
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
    if (values.find(_name) == values.end())
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
        else
        {
            g_Log.warning(name<T>() + " value \"" + _name + "\" not defined, defaulting");
        }
        return _default;
    }
    Value* value = values[_name];
    assert(dynamic_cast<TemplateBaseValue<T>*>(value));
    TemplateBaseValue<T>* typedValue = (TemplateBaseValue<T>*)value;
    return typedValue->get();
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
                TemplateValue<T>* value = types[name<T>()]->instance(_default);
                undefinedLog[_name] = value;
                return value->get();
            }
        }
        else
        {
            g_Log.warning(name<T>() + " value \"" + _name + "\" not defined, defaulting");
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
    types[_name] = _newFactory;
    name<T>() = _name;
}
template <typename T>
TypeTable::AutomaticRegister<T>::AutomaticRegister()
{
    delete types[name<T>()];
    types[name<T>()] = new TemplateType<T>();
}
template <typename T>
void TypeTable::AutomaticRegister<T>::check()
{
}
template <typename T>
TypeTable::AutomaticRegister<T> TypeTable::TemplateType<T>::staticRegister;
#endif // TYPETABLE_H
