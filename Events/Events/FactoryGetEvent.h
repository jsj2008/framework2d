#ifndef FACTORYGETEVENT_H
#define FACTORYGETEVENT_H

#include <Events/Event.h>
#include <string>

class FactoryGetEvent : public Event
{
    public:
        FactoryGetEvent(const std::string& _name);
        virtual ~FactoryGetEvent();
        const std::string& getName(){return name;}
    protected:
    private:
        std::string name;
};

#endif // FACTORYGETEVENT_H
