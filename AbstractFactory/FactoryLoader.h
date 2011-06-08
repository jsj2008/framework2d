#ifndef FACTORYLOADER_H
#define FACTORYLOADER_H


#include <fstream>
#include <string>
#include <unordered_map>

#include <Types/Vec2f.h>
#include <Types/DynamicTypeTable.h>

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
        /// Default is a keyword, so I called it "normal" :(
        template <typename T>
        T get(const std::string& name, const T& normal);
        template <typename T>
        void addType(const std::string& name);
    protected:
    private:
        std::ifstream file;
        std::string type, name;
        void syntaxError(const std::string& message);
        void warning(const std::string& message);
        DynamicTypeTable mvalues; // FIXME use this instead
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
    return mvalues.popValue<T>(name, normal);
}
#endif // FACTORYLOADER_H
