#ifndef FACTORYLOADER_H
#define FACTORYLOADER_H

#define GCC_EXTENSION_DEMANGLER

#include <fstream>
#include <string>
#include <unordered_map>

#ifdef GCC_EXTENSION_DEMANGLER
#include <cxxabi.h>
#endif

#include <Types/Vec2f.h>

namespace FactoryLoaderPrivate
{
    class Value;
    class Type;
}

class FactoryLoader
{
    public:
        FactoryLoader(const char* filename);
        virtual ~FactoryLoader();
        bool next();
        void end();
        const std::string& getType(){return type;}
        const std::string& getName(){return name;}
        template <typename T>
        /// Default is a keyword, so I called it "normal" :(
        T get(const std::string& name, const T& normal);
        template <typename T>
        void addType(const std::string& name);
    protected:
    private:
        std::ifstream file;
        std::string type, name;
        void syntaxError(const std::string& message);
        void warning(const std::string& message);
        std::unordered_map<std::string,FactoryLoaderPrivate::Value*> values;
        std::unordered_map<std::string,FactoryLoaderPrivate::Type*> types;
};

#include <typeinfo>
namespace FactoryLoaderPrivate
{
    class Value
    {
        public:
            virtual ~Value(){}
            virtual const std::string name()=0;
    };
    template <typename T>
    class TemplateValue : public Value
    {
        public:
            TemplateValue(const T& _value){value = _value;}
            const T& get(){return value;}
            void set(const T& _value){value = _value;}
            const std::string name(){return std::string(typeid(T).name());}
        T value;
    };
    class Type
    {
        public:
            virtual ~Type(){}
            virtual Value* instance(std::ifstream* file)=0;
    };
    template <typename T>
    class TemplateType : public Type
    {
        public:
            Value* instance(std::ifstream* file)
            {
                T value;
                (*file) >> value;
                return new TemplateValue<T>(value);
            }
    };
}

template <typename T>
T FactoryLoader::get(const std::string& name, const T& normal)
{
    using namespace FactoryLoaderPrivate;
    auto value = values.find(name);
    if (value == values.end())
    {
#ifdef GCC_EXTENSION_DEMANGLER
        char* demangledName = abi::__cxa_demangle(typeid(T).name(),0,0,NULL);
        warning(std::string(demangledName) + " value \"" + name + "\" not defined, defaulting");
        free(demangledName);
#else
        warning(std::string(typeid(T).name()) + " value \"" + name + "\" not defined, defaulting");
#endif
        return normal;
    }
    else
    {
        TemplateValue<T>* ret = dynamic_cast<TemplateValue<T>*>(value->second);
        if (ret == NULL)
        {
            warning("Variable " + name + " is not of type " + typeid(T).name());
        }
        T templateRet = ret->get();
        values.erase(value);
        return templateRet;
    }
}
#endif // FACTORYLOADER_H
