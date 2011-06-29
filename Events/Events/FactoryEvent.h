#ifndef FACTORYEVENT_H
#define FACTORYEVENT_H

#include <Events/Event.h>

template <typename Product>
class FactoryEvent : public Event
{
    public:
        FactoryEvent(Product* _product)
        {
            //ctor
            product = _product;
        }
        virtual ~FactoryEvent()
        {
            //dtor
        }
        Product* get(){return product;}
    protected:
    private:
        Product* product;
};

#endif // FACTORYEVENT_H
