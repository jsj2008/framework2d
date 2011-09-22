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
    protected:
        class Value;
    public:
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

        std::unordered_map<ValueIndex,Value*>::iterator begin();
        std::unordered_map<ValueIndex,Value*>::iterator end();

        std::vector<std::string> getUndefinedLog();

        // Don't use these unless neccessary, use the functions in the base class unless you're reading from file or something
        Value* addDynamicValue(const TypeIndex& type, const ValueIndex& name);
        void addDynamicValue(const TypeIndex& type, const ValueIndex& name, std::istream* parseSource);

        void removeValue(const ValueIndex& name);
        void clear();

        void output(std::ostream *out);
        friend std::ostream& operator<< (std::ostream &out, const TypeTable &table);
        friend std::istream& operator>> (std::istream &in, TypeTable &table);

    protected:
        std::unordered_map<ValueIndex,Value*> values;

        class Value
        {
            public:
                virtual ~Value(){}
                virtual void set(std::istream* parseSource)=0;
                virtual void output(std::ostream* parseDestination)=0;
                virtual std::string getTypeId()=0;
                virtual Value* clone()=0;
        };
        class UntypedValue : public Value
        {
            public:
                UntypedValue(TypeIndex _type, const ValueIndex& _name);
                ~UntypedValue();
                void set(std::istream* parseSource); /// FIXME make this something more generic, when I figure out the input type
                void output(std::ostream* parseDestination);
                std::string getTypeId();
                Value* clone();
                template <typename T>
                Value* instance();
                std::string getValueIndex(){return name;}
            private:
                std::string unparsedValue;
                ValueIndex name;
                TypeIndex type;
        };
        template <typename T>
        class TemplateValue : public Value
        {
            public:
                TemplateValue(){}
                TemplateValue(const T& _value){value = _value;}
                void set(const T& _value){value = _value;}
                void set(std::istream* parseSource){(*parseSource) >> value;}
                void output(std::ostream* parseDestination){(*parseDestination) << value;}
                const T& get(){return value;}
                std::string getTypeId(){return name<T>();}
                Value* clone(){return new TemplateValue<T>(value);}
            private:
                T value;
        };
        template <typename T>
        class AutomaticRegister
        {
            public:
                AutomaticRegister();
                void check();
        };
        class Type
        {
            public:
                Type(){}
                virtual ~Type(){}
                virtual Value* instance()=0;
                virtual Type* clone()=0;
        };
        template <typename T>
        class TemplateType : public Type
        {
            public:
                TemplateType(){staticRegister.check();}
                Value* instance(){return new TemplateValue<T>();}
                Type* clone(){return new TemplateType<T>();}
            private:
                static AutomaticRegister<T> staticRegister;
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
void TypeTable::addValue(const ValueIndex& name, const T& value)
{
    if(values.find(name) != values.end())
    {
        delete values[name];
    }
    values[name] = new TemplateValue<T>(value);
}

template <typename T>
void TypeTable::setValue(const ValueIndex& name, const T& _value)
{
    assert(values.find(name) != values.end());
    Value* value = values[name];
    assert(dynamic_cast<TemplateValue<T>*>(value));
    TemplateValue<T>* typedValue = (TemplateValue<T>*)value;
    typedValue->set(_value);
}

template <typename T>
const T& TypeTable::getValue(const ValueIndex& name)
{
    assert(values.find(name) != values.end());
    Value* value = values[name];
    assert(dynamic_cast<TemplateValue<T>*>(value));
    TemplateValue<T>* typedValue = static_cast<TemplateValue<T>*>(value);
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
                undefinedLog[_name] = new TemplateValue<T>(_default);
        }
        else
        {
            g_Log.warning(name<T>() + " value \"" + _name + "\" not defined, defaulting");
        }
        return _default;
    }
    Value* value = values[_name];
    assert(dynamic_cast<TemplateValue<T>*>(value));
    TemplateValue<T>* typedValue = (TemplateValue<T>*)value;
    return typedValue->get();
}

template <typename T>
const T TypeTable::popValue(const ValueIndex& _name, const T& _default)
{
    if (values.find(_name) == values.end())
    {
        if (logUndefined)
        {
            if (undefinedLog.find(_name) == undefinedLog.end())
                undefinedLog[_name] = new TemplateValue<T>(_default);
        }
        else
        {
            g_Log.warning(name<T>() + " value \"" + _name + "\" not defined, defaulting");
        }
        return _default;
    }
    Value* value = values[_name];
    assert(dynamic_cast<TemplateValue<T>*>(value));
    TemplateValue<T>* typedValue = (TemplateValue<T>*)value;
    T ret = typedValue->get();
    delete typedValue;
    values.erase(_name);
    return ret;
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
