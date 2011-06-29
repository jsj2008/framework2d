#ifndef FACTORYEVENTHANDLER_H
#define FACTORYEVENTHANDLER_H

#include <Events/EventHandler.h>

template <typename Product>
class FactoryEventHandler : public EventHandler
{
    public:
        FactoryEventHandler();
        virtual ~FactoryEventHandler();
        bool trigger(Event* event);
    protected:
    private:
};

#endif // FACTORYEVENTHANDLER_H
