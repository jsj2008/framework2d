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
        FactoryLoader(AbstractFactories* _factories, bool logUndefined = false);
        FactoryLoader(const std::string& _type, const std::string& _name, TypeTable* _table, AbstractFactories* _factories);
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
        template <typename Type>
        const std::vector<Type>& getArray(const std::string& name, const std::vector<Type>& _default);
        template <typename Product>
        AbstractFactoryBase<Product>* getFactory(const std::string& name, const char* _default);
        template <typename Product>
        std::vector<AbstractFactoryBase<Product>*> getFactoryArray(const std::string& name, const std::vector<std::string>& _default);
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
        return mvalues.getFactories()->getFactory<Product>(mvalues.popValue<std::string>(_name, _default));
    }
    catch (int i)
    {
        auto factory = mvalues.getFactories()->getFactory<Product>(_default);
        if (mvalues.loggingUndefined())
        {
            mvalues.addValue<AbstractFactoryBase<Product>*>(_name, factory);
        }
        return factory;
    }
}
template <typename Type>
const std::vector<Type>& FactoryLoader::getArray(const std::string& name, const std::vector<Type>& _default)
{
    return mvalues.getArray(name, _default);
}

template <typename Product>
std::vector<AbstractFactoryBase<Product>*> FactoryLoader::getFactoryArray(const std::string& name, const std::vector<std::string>& _default)
{
    const std::vector<std::string>& stringValues = mvalues.getArray(name, _default);
    std::vector<AbstractFactoryBase<Product>*> returnValues;
    returnValues.resize(stringValues.size());
    for (unsigned int i = 0; i != stringValues.size(); i++)
    {
        returnValues[i] =  mvalues.getFactories()->getFactory<Product>(stringValues[i]);
        /*}
        catch (int i)
        {
            auto factory = mvalues.getFactories()->getFactory<Product>(_default);
            if (mvalues.loggingUndefined())
            {
                mvalues.addValue<AbstractFactoryBase<Product>*>(_name, factory);
            }
            returnValues[i] =  factory;
        }*/
    }
    return returnValues;
}
#endif // FACTORYLOADER_H






























