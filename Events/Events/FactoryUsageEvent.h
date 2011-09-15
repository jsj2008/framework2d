#ifndef FACTORYUSAGEEVENT_H
#define FACTORYUSAGEEVENT_H

#include <Events/Event.h>
/**
    Base class for all factory usage events
**/
template <typename Product>
class FactoryUsageEvent : public Event
{
    public:
        FactoryUsageEvent(Product* _product)
        {
            //ctor
            product = _product;
        }
        virtual ~FactoryUsageEvent()
        {
            //dtor
        }
        Product* get(){return product;}
    protected:
    private:
        Product* product;
};

#endif // FACTORYUSAGEEVENT_H
