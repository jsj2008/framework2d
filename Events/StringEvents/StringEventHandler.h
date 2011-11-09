#ifndef STRINGEVENTHANDLER_H
#define STRINGEVENTHANDLER_H

#include <unordered_map>
#include <string>

class StringEventListener;

class StringEventHandler
{
    private:
        class EventHandler;
    public:
        class EventFirer
        {
            public:
                EventFirer();
                ~EventFirer();
                void fire();
            private:
                EventHandler* handler;
        };
        StringEventHandler();
        virtual ~StringEventHandler();
    protected:
    private:
        class EventHandler
        {
            public:
                EventHandler();
                ~EventHandler();
                void fire();
            private:
                std::string name;
                StringEventListener* listenerList;
        };
        std::unordered_map<std::string, EventHandler*> handlerMap;
};

#endif // STRINGEVENTHANDLER_H
