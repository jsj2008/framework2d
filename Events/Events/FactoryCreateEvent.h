#ifndef FACTORYCREATEEVENT_H
#define FACTORYCREATEEVENT_H

#include <Events/Event.h>
#include <AbstractFactory/AbstractFactory.h>

template <typename Product>
class FactoryCreateEvent : public Event
{
    public:
        FactoryCreateEvent(AbstractFactoryBase<Product>* _factory, const std::string& _factoryName);
        virtual ~FactoryCreateEvent();
        AbstractFactoryBase<Product>* getFactory(){return factory;}
        const std::string& getFactoryName(){return factory->getName();}
        static std::vector<std::pair<AbstractFactoryBase<Product>*, std::string>> factories;
    protected:
    private:
        AbstractFactoryBase<Product>* factory;
        std::string factoryName;
};

template <typename Product>
FactoryCreateEvent<Product>::FactoryCreateEvent(AbstractFactoryBase<Product>* _factory, const std::string& _factoryName)
{
    //ctor
    factory = _factory;
    factoryName = _factoryName;
    factories.push_back({factory, factoryName});
}

template <typename Product>
FactoryCreateEvent<Product>::~FactoryCreateEvent()
{
    //dtor
}

template <typename Product>
std::vector<std::pair<AbstractFactoryBase<Product>*, std::string>> FactoryCreateEvent<Product>::factories;
#endif // FACTORYCREATEEVENT_H
