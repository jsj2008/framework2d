#ifndef FACTORYINSTANCEEVENT_H
#define FACTORYINSTANCEEVENT_H

#include <string>
#include <Events/Events/FactoryTypeEvent.h>

template <typename Product, typename Factory>
class FactoryInstanceEvent : public FactoryTypeEvent<Product, Factory>
{
    public:
        FactoryInstanceEvent(Product* _product, const std::string& _name);
        virtual ~FactoryInstanceEvent();
    protected:
    private:
        std::string name;
};

/**
* Implementation
*/

template <typename Product, typename Factory>
FactoryInstanceEvent<Product,Factory>::FactoryInstanceEvent(Product* _product, const std::string& _name)
:FactoryTypeEvent<Product, Factory>(_product),
name(_name)
{
    //ctor
}

template <typename Product, typename Factory>
FactoryInstanceEvent<Product,Factory>::~FactoryInstanceEvent()
{
    //dtor
}

#endif // FACTORYINSTANCEEVENT_H
