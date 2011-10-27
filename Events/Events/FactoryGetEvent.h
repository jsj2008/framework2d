#ifndef FACTORYGETEVENT_H
#define FACTORYGETEVENT_H
/*
#include <Events/Event.h>
template <typename Product>
class AbstractFactoryBase;
#include <string>

template <typename Product>
class FactoryGetEvent : public Event
{
    public:
        FactoryGetEvent(AbstractFactoryBase<Product>* _factory);
        virtual ~FactoryGetEvent();
        const std::string& getName();
        const AbstractFactoryBase<Product>* getFactory(){return factory;}
    protected:
    private:
        AbstractFactoryBase<Product>* factory;
};

#include <AbstractFactory/AbstractFactory.h>

template <typename Product>
FactoryGetEvent<Product>::FactoryGetEvent(AbstractFactoryBase<Product>* _factory)
{
    //ctor
    factory = _factory;
}

template <typename Product>
FactoryGetEvent<Product>::~FactoryGetEvent()
{
    //dtor
}

template <typename Product>
const std::string& FactoryGetEvent<Product>::getName()
{
    //ctor
    return factory->getInstanceName();
}*/
#endif // FACTORYGETEVENT_H
