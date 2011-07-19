#ifndef FACTORYTYPEEVENT_H
#define FACTORYTYPEEVENT_H

#include <Events/Events/FactoryEvent.h>

template <typename Product, typename Factory>
class FactoryTypeEvent : public FactoryEvent<Product>
{
    public:
        FactoryTypeEvent(Product* _product);
        virtual ~FactoryTypeEvent();
    protected:
    private:
};

/**
* Implementation
*/

template <typename Product, typename Factory>
FactoryTypeEvent<Product,Factory>::FactoryTypeEvent(Product* _product)
:FactoryEvent<Product>(_product)
{
    //ctor
}

template <typename Product, typename Factory>
FactoryTypeEvent<Product,Factory>::~FactoryTypeEvent()
{
    //dtor
}

#endif // FACTORYTYPEEVENT_H
