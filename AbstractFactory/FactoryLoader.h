#include <AbstractFactory/AbstractFactory.h>
#ifndef FACTORYLOADER_H
#define FACTORYLOADER_H


#include <fstream>
#include <string>
#include <unordered_map>

#include <Types/Vec2f.h>
#include <Types/TypeTable.h>

namespace FactoryLoaderPrivate
{
    class Value;
    class Type;
}

class FactoryLoader
{
    public:
        FactoryLoader(bool logUndefined = false);
        virtual ~FactoryLoader();
        virtual bool isValid()=0;
        virtual bool next()=0;
        void end();
        const std::string& getType(){return type;}
        const std::string& getName(){return name;}
        /// Default is a keyword, so I called it "normal" :(
        template <typename T>
        T get(const std::string& name, const T& normal);
        template <typename T>
        T get(const std::string& name);
        template <typename Product>
        AbstractFactoryBase<Product>* getFactory(const std::string& name, const char* _default);
        template <typename T>
        void addType(const std::string& name);

        TypeTable* getTypeTable(){return &mvalues;}
    protected:
        std::string type, name;
        void syntaxError(const std::string& message);
        void warning(const std::string& message);
        TypeTable mvalues;
    private:
};

#include <typeinfo>

template <typename T>
T FactoryLoader::get(const std::string& _name, const T& normal)
{
    return mvalues.popValue<T>(_name, normal);
}
template <typename T>
T FactoryLoader::get(const std::string& _name)
{
    return mvalues.popValue<T>(_name);
}
template <typename Product>
AbstractFactoryBase<Product>* FactoryLoader::getFactory(const std::string& _name, const char* _default)
{
    try
    {
        return mvalues.popValue<AbstractFactoryBase<Product>*>(_name);
    }
    catch (int i)
    {
        return AbstractFactories::global().getFactory<Product>(_default);
    }
}
#endif // FACTORYLOADER_H
