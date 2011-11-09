#ifndef STRINGEVENTLISTENER_H
#define STRINGEVENTLISTENER_H


class StringEventListener
{
    public:
        StringEventListener();
        virtual ~StringEventListener();
        virtual void trigger()=0;
    protected:
    private:
        StringEventListener* next,* prev;
};

#endif // STRINGEVENTLISTENER_H
