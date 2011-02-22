#ifndef CLICKEVENT_H
#define CLICKEVENT_H

#include <Types/Vec2i.h>
struct Rect
{
    Rect(int _x, int _y, int _x2, int _y2);
    int x,y,x2,y2; /// Screen space coordinates
    bool contained(Vec2i mouse);
};
class ClickEvent
{
    public:
        ClickEvent(const Rect& _Rect);
        virtual ~ClickEvent();
        virtual void render(){}
        virtual bool buttonDown(Vec2i mouse, unsigned char button)=0;
        virtual void mouseMove(Vec2i mouse)=0;
        virtual void buttonUp(Vec2i mouse, unsigned char button)=0;
    protected:
        Rect mRect;
    private:
};

#endif // CLICKEVENT_H
