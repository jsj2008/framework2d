#ifndef EVENTFACTORY_H
#define EVENTFACTORY_H


class EventFactory
{
    public:
        EventFactory();
        virtual ~EventFactory();
        virtual void factorySelected()=0;
    protected:
    private:
};

#endif // EVENTFACTORY_H
