#ifndef TRIGGERLISTENER_H
#define TRIGGERLISTENER_H

class TriggerButton;

class TriggerListener
{
    public:
        TriggerListener();
        virtual ~TriggerListener();
        virtual void trigger(TriggerButton* button, unsigned char mouseButton)=0;
    protected:
    private:
};

#endif // TRIGGERLISTENER_H
