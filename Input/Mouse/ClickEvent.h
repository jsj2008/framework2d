#ifndef CLICKEVENT_H
#define CLICKEVENT_H

struct Rect
{
    Rect(int _x, int _y, int _x2, int _y2);
    int x,y,x2,y2; /// Screen space coordinates
    bool contained(int mouseX, int mouseY);
};
class ClickEvent
{
    public:
        ClickEvent(const Rect& _Rect);
        virtual ~ClickEvent();
        virtual bool buttonDown(int mouseX, int mouseY)=0;
        virtual void mouseMove(int mouseX, int mouseY)=0;
        virtual void buttonUp(int mouseX, int mouseY)=0;
    protected:
        Rect mRect;
    private:
};

#endif // CLICKEVENT_H
