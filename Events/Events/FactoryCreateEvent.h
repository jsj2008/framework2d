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
        const std::string& getFactoryName(){return factoryName;}
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
}

template <typename Product>
FactoryCreateEvent<Product>::~FactoryCreateEvent()
{
    //dtor
}

#endif // FACTORYCREATEEVENT_H
