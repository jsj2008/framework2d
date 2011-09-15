#ifndef FACTORYTYPEREGISTEREVENT_H
#define FACTORYTYPEREGISTEREVENT_H

#include <Events/Event.h>
#include <string>
#include <vector>
/**
    When a factory type is registered (usually before the main loop is entered) this is called with its type-name
**/
template <typename Product>
class FactoryTypeRegisterEvent : public Event
{
    public:
        FactoryTypeRegisterEvent(const std::string& _factoryName);
        virtual ~FactoryTypeRegisterEvent();
        const std::string& getFactoryName(){return factoryName;}
    protected:
    private:
        std::string factoryName;
        friend class DynamicEditor;
};

/**
* Implementation
*/

template <typename Product>
FactoryTypeRegisterEvent<Product>::FactoryTypeRegisterEvent(const std::string& _factoryName)
:factoryName(_factoryName)
{
    //ctor
}

template <typename Product>
FactoryTypeRegisterEvent<Product>::~FactoryTypeRegisterEvent()
{
    //dtor
}

#endif // FACTORYTYPEREGISTEREVENT_H
