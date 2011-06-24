#ifndef ABSTRACTFACTORYLIST_H
#define ABSTRACTFACTORYLIST_H

#include <string>
typedef std::string AbstractFactoryReference;
#include <unordered_map>
template <typename Product>
class FactoryCreator;
template <typename Product>
class AbstractFactoryBase;
class FactoryParameters;

class AbstractFactoryListBase
{
    public:
        AbstractFactoryListBase(std::unordered_map<std::string, AbstractFactoryListBase*>* factoryLists, const std::string& productName);
        virtual ~AbstractFactoryListBase();
        virtual void init()=0;
    protected:
    private:
};

template <typename Product>
class AbstractFactoryList: private AbstractFactoryListBase
{
    public:
        AbstractFactoryList(std::unordered_map<std::string, AbstractFactoryListBase*>* factoryLists);
        void init();
        virtual ~AbstractFactoryList();
        template <typename Factory>
        void registerFactoryType(const std::string& name);
        Product* useFactory(AbstractFactoryReference factory, FactoryParameters* parameters = NULL);
        const std::string getProductName();
    protected:
    private:
        const std::string& productName();
        std::unordered_map<std::string,FactoryCreator<Product>*> factoryCreators;
        std::unordered_map<AbstractFactoryReference,AbstractFactoryBase<Product>*> factories;
};

#include <AbstractFactory/FactoryParameters.h>
#include <AbstractFactory/AbstractFactory.h>
#include <AbstractFactory/FactoryLoader.h>

template <typename Product>
Product* AbstractFactoryList<Product>::useFactory(AbstractFactoryReference factory, FactoryParameters* parameters)
{
    if (parameters == NULL)
    {
        static FactoryParameters params;
        //params.clear();
        return factories[factory]->use(&params);
    }
    return factories[factory]->use(parameters);
}
class FactoryLoader;
template <typename Product>
class FactoryCreator
{
    public:
        virtual AbstractFactoryBase<Product>* createFactory(FactoryLoader* loader)=0;
};

template <typename Product, typename Factory>
class TemplateFactoryCreator : public FactoryCreator<Product>
{
    public:
        AbstractFactoryBase<Product>* createFactory(FactoryLoader* loader){return new Factory(loader);}
};

template <typename Product>
template <typename Factory>
void AbstractFactoryList<Product>::registerFactoryType(const std::string& name)
{
    auto creator = new TemplateFactoryCreator<Product, Factory>;
    factoryCreators[name] = creator;
    static FactoryLoader emptyConfig(NULL);
    factories[name] = creator->createFactory(&emptyConfig);
}
template <typename Product>
void AbstractFactoryList<Product>::init()
{
    FactoryLoader loader(("Resources/" + getProductName() + "Factories.txt").c_str());
    while (loader.next())
    {
        assert(factories.find(loader.getName()) == factories.end());
        factories[loader.getName()] = factoryCreators[loader.getType()]->createFactory(&loader);
        loader.end();
    }
}
template <typename Product>
AbstractFactoryList<Product>::AbstractFactoryList(std::unordered_map<std::string, AbstractFactoryListBase*>* factoryLists)
:AbstractFactoryListBase(factoryLists, getProductName())
{
    //ctor
}

template <typename Product>
AbstractFactoryList<Product>::~AbstractFactoryList()
{
    //dtor
}

#include <cxxabi.h>

template <typename Type>
std::string demangle()
{
    const std::type_info  &ti = typeid(Type);
    char* realname;
    int status;
    realname = abi::__cxa_demangle(ti.name(), 0, 0, &status);
    std::string ret(realname);
    free(realname);
    return ret;
}
#define HAS_MEM_FUNC(func, name)                                        \
    template<typename T, typename Sign>                                 \
    struct name {                                                       \
        typedef char yes[1];                                            \
        typedef char no [2];                                            \
        template <typename U, U> struct type_check;                     \
        template <typename _1> static yes &chk(type_check<Sign, &_1::func> *); \
        template <typename   > static no  &chk(...);                    \
        static bool const value = sizeof(chk<T>(0)) == sizeof(yes);     \
    }


template<bool C, typename T = void>
struct enable_if {
  typedef T type;
};

template<typename T>
struct enable_if<false, T> { };

HAS_MEM_FUNC(name, has_to_string);

template<typename T>
typename enable_if<has_to_string<T, std::string(T::*)()>::value, std::string>::type doSomething(T * t)
{
   /* something when T has name ... */
   return T::name();
}

template<typename T>
typename enable_if<!has_to_string<T, std::string(T::*)()>::value, std::string>::type doSomething()
{
   /* something when T doesnt have name ... */
   return demangle<T>();
}

/*AbstractFactoryListBase::AbstractFactoryListBase(std::unordered_map<std::string, AbstractFactoryListBase*>* factoryLists, const std::string& productName)
{
    (*factoryLists)[productName] = this;
}*/

template <typename Product>
const std::string AbstractFactoryList<Product>::getProductName()
{
    return doSomething<Product>();
}

#endif // ABSTRACTFACTORYLIST_H
