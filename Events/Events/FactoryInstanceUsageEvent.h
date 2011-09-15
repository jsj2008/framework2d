#ifndef FACTORYINSTANCEUSAGEEVENT_H
#define FACTORYINSTANCEUSAGEEVENT_H

#include <string>
#include <Events/Events/FactoryTypeUsageEvent.h>
/**
    When a factory is used, one of these is triggered with its name
**/
template <typename Product, typename Factory>
class FactoryInstanceUsageEvent : public FactoryTypeUsageEvent<Product, Factory>
{
    public:
        FactoryInstanceUsageEvent(Product* _product, const std::string& _name);
        virtual ~FactoryInstanceUsageEvent();
    protected:
    private:
        std::string name;
};

/**
* Implementation
*/

template <typename Product, typename Factory>
FactoryInstanceUsageEvent<Product,Factory>::FactoryInstanceUsageEvent(Product* _product, const std::string& _name)
:FactoryTypeUsageEvent<Product, Factory>(_product),
name(_name)
{
    //ctor
}

template <typename Product, typename Factory>
FactoryInstanceUsageEvent<Product,Factory>::~FactoryInstanceUsageEvent()
{
    //dtor
}

#endif // FACTORYINSTANCEUSAGEEVENT_H
