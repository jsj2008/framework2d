#ifndef TYPETABLE_H
#define TYPETABLE_H

#define GCC_EXTENSION_DEMANGLER
#ifdef GCC_EXTENSION_DEMANGLER
#include <cxxabi.h>
#endif

#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <Types/Vec2f.h>
#include <Log/Log.h>

class TypeTable
{
    public:
        typedef std::string ValueIndex;
        TypeTable(){}
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

        void removeValue(const ValueIndex& name);
        void clear();

    protected:
    protected:
        class Value;
        std::unordered_map<ValueIndex,Value*> values;

        class Value
        {
            public:
                virtual ~Value(){}
                virtual void set(std::istream* parseSource)=0;
                virtual void output(std::ostream* parseDestination)=0;
                virtual std::string getTypeId()=0;
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
                std::string getTypeId(){return (typeid(T).name());}
            private:
                T value;
        };
};

template <typename T>
std::istream& operator>> (std::istream &in, std::vector<T> &elements);
template <typename T>
std::ostream& operator<< (std::ostream &out, const std::vector<T> &elements);

template <typename T>
void TypeTable::addValue(const ValueIndex& name, const T& value)
{
    assert(values.find(name) == values.end());
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
    TemplateValue<T>* typedValue = (TemplateValue<T>*)value;
    return typedValue->get();
}

template <typename T>
const T& TypeTable::getValue(const ValueIndex& name, const T& _default)
{
    if (values.find(name) == values.end())
    {
#ifdef GCC_EXTENSION_DEMANGLER
        char* demangledName = abi::__cxa_demangle(typeid(T).name(),0,0,NULL);
        g_Log.warning(std::string(demangledName) + " value \"" + name + "\" not defined, defaulting");
        free(demangledName);
#else
        g_Log.warning(std::string(typeid(T).name()) + " value \"" + name + "\" not defined, defaulting");
#endif
        return _default;
    }
    Value* value = values[name];
    assert(dynamic_cast<TemplateValue<T>*>(value));
    TemplateValue<T>* typedValue = (TemplateValue<T>*)value;
    return typedValue->get();
}

template <typename T>
const T TypeTable::popValue(const ValueIndex& name, const T& _default)
{
    if (values.find(name) == values.end())
    {
#ifdef GCC_EXTENSION_DEMANGLER
        char* demangledName = abi::__cxa_demangle(typeid(T).name(),0,0,NULL);
        g_Log.warning(std::string(demangledName) + " value \"" + name + "\" not defined, defaulting");
        free(demangledName);
#else
        g_Log.warning(std::string(typeid(T).name()) + " value \"" + name + "\" not defined, defaulting");
#endif
        return _default;
    }
    Value* value = values[name];
    assert(dynamic_cast<TemplateValue<T>*>(value));
    TemplateValue<T>* typedValue = (TemplateValue<T>*)value;
    T ret = typedValue->get();
    delete typedValue;
    values.erase(name);
    return ret;
}
#endif // TYPETABLE_H
