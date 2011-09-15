#ifndef FACTORYTYPEUSAGEEVENT_H
#define FACTORYTYPEUSAGEEVENT_H

#include <Events/Events/FactoryUsageEvent.h>

/**
    When a factory is used, one of these is triggered with its type-name
**/
template <typename Product, typename Factory>
class FactoryTypeUsageEvent : public FactoryUsageEvent<Product>
{
    public:
        FactoryTypeUsageEvent(Product* _product);
        virtual ~FactoryTypeUsageEvent();
    protected:
    private:
};

/**
* Implementation
*/

template <typename Product, typename Factory>
FactoryTypeUsageEvent<Product,Factory>::FactoryTypeUsageEvent(Product* _product)
:FactoryUsageEvent<Product>(_product)
{
    //ctor
}

template <typename Product, typename Factory>
FactoryTypeUsageEvent<Product,Factory>::~FactoryTypeUsageEvent()
{
    //dtor
}

#endif // FACTORYTYPEUSAGEEVENT_H
