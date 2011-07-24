#ifndef FACTORYTYPEREGISTEREVENT_H
#define FACTORYTYPEREGISTEREVENT_H

#include <Events/Event.h>
#include <string>
#include <vector>

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
        static std::vector<std::string> factoryNames; /// FIXME
};

/**
* Implementation
*/

template <typename Product>
FactoryTypeRegisterEvent<Product>::FactoryTypeRegisterEvent(const std::string& _factoryName)
:factoryName(_factoryName)
{
    //ctor
    factoryNames.push_back(factoryName);
}

template <typename Product>
FactoryTypeRegisterEvent<Product>::~FactoryTypeRegisterEvent()
{
    //dtor
}

template <typename Product>
std::vector<std::string> FactoryTypeRegisterEvent<Product>::factoryNames;
#endif // FACTORYTYPEREGISTEREVENT_H
