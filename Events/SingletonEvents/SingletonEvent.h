#ifndef SINGLETONEVENT_H
#define SINGLETONEVENT_H

template <typename DerivedEvent>
class SingletonEvent
{
    public:
        SingletonEvent();
        virtual ~SingletonEvent();
        void trigger();
    protected:
    private:
};

#include <Events/SingletonEvents/SingletonEventHandler.h>
template <typename DerivedEvent>
SingletonEvent<DerivedEvent>::SingletonEvent()
{
    //ctor
}

template <typename DerivedEvent>
SingletonEvent<DerivedEvent>::~SingletonEvent()
{
    //dtor
}

template <typename DerivedEvent>
void SingletonEvent<DerivedEvent>::trigger()
{
    SingletonEventHandler<DerivedEvent>::singleton().trigger(static_cast<DerivedEvent*>(this));
}
#endif // SINGLETONEVENT_H
