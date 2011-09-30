#ifndef NAMEDFACTORYUSAGEEVENT_H
#define NAMEDFACTORYUSAGEEVENT_H

#include <Events/Event.h>
#include <string>

template <typename Product>
class NamedFactoryUsageEvent : public Event
{
    public:
        NamedFactoryUsageEvent(Product* _product, const std::string& _name)
        {
            //ctor
            product = _product;
            name = _name;
        }
        virtual ~NamedFactoryUsageEvent()
        {
            //dtor
        }
        Product* get(){return product;}
        const std::string& getName(){return name;}
    protected:
    private:
        Product* product;
        std::string name;
};

#endif // NAMEDFACTORYUSAGEEVENT_H
