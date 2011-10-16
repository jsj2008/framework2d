#ifndef SINGLETONEVENTLISTENER_H
#define SINGLETONEVENTLISTENER_H

template <typename EventType>
class SingletonEventHandler;

template <typename EventType>
class SingletonEventListener
{
    public:
        SingletonEventListener();
        virtual ~SingletonEventListener();
        virtual bool trigger(EventType* event)=0; /// Do I keep listening?
    protected:
    private:
        friend class SingletonEventHandler<EventType>;
        SingletonEventListener<EventType>* prev,* next;
};

template <typename EventType>
SingletonEventListener<EventType>::SingletonEventListener()
{
    //ctor
    prev = next = nullptr;
}

template <typename EventType>
SingletonEventListener<EventType>::~SingletonEventListener()
{
    //dtor
}

#endif // SINGLETONEVENTLISTENER_H
