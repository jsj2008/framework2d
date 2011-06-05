#ifndef ABSTRACTFACTORYLIST_H
#define ABSTRACTFACTORYLIST_H

#include <string>
typedef std::string AbstractFactoryReference;
#include <unordered_map>
class AbstractFactory;
class FactoryParameters;
class Entity;
class FactoryCreator;

extern class AbstractFactoryList
{
    public:
        AbstractFactoryList();
        virtual ~AbstractFactoryList();
        template <typename T>
        void registerFactoryType(const std::string& name);
        Entity* useFactory(AbstractFactoryReference factory, FactoryParameters* parameters = NULL);
        void addFactory(AbstractFactoryReference name, AbstractFactory* factory);
    protected:
    private:
        std::unordered_map<std::string,FactoryCreator*> factoryCreators;
        std::unordered_map<AbstractFactoryReference,AbstractFactory*> factories;
}g_AbstractFactoryList;

#endif // ABSTRACTFACTORYLIST_H
