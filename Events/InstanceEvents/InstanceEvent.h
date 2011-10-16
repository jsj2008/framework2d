#ifndef INSTANCEEVENT_H
#define INSTANCEEVENT_H

template <typename DerivedEvent>
class InstanceEvent
{
    public:
        InstanceEvent();
        virtual ~InstanceEvent();
    protected:
    private:
};

template <typename DerivedEvent>
InstanceEvent<DerivedEvent>::InstanceEvent()
{
    //ctor
}

template <typename DerivedEvent>
InstanceEvent<DerivedEvent>::~InstanceEvent()
{
    //dtor
}

#endif // INSTANCEEVENT_H
