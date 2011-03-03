#ifndef TRIGGERBUTTON_H
#define TRIGGERBUTTON_H

#include <Input/Mouse/ClickReleaseEvent.h>
class TriggerListener;

class TriggerButton : public ClickReleaseEvent
{
    public:
        TriggerButton(const Rect _rect, TriggerListener* _listener);
        virtual ~TriggerButton();
        void click(Vec2i mouse, unsigned char button);
        void render();
    protected:
    private:
        TriggerListener* listener;
};

#endif // TRIGGERBUTTON_H
