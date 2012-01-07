#ifndef INSTANCEEVENTLISTENER_H
#define INSTANCEEVENTLISTENER_H

template <typename DerivedEvent>
class InstanceEventHandler;

template <typename DerivedEvent>
class InstanceEventListener
{
    public:
        InstanceEventListener();
        virtual ~InstanceEventListener();
        virtual bool trigger(DerivedEvent* _event)=0;
        virtual void handlerDestroyed(){}
    protected:
    private:
        friend class InstanceEventHandler<DerivedEvent>;
        InstanceEventListener<DerivedEvent>* next,* prev;
};


template <typename DerivedEvent>
InstanceEventListener<DerivedEvent>::InstanceEventListener()
{
    //ctor
    next = prev = nullptr;
}

template <typename DerivedEvent>
InstanceEventListener<DerivedEvent>::~InstanceEventListener()
{
    //dtor
}

#endif // INSTANCEEVENTLISTENER_H
