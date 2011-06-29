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
        FactoryLoader();
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
        void addType(const std::string& name);
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
#endif // FACTORYLOADER_H
