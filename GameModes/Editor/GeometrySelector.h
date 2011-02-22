#ifndef GEOMETRYSELECTOR_H
#define GEOMETRYSELECTOR_H

#include <Input/Mouse/ClickDragEvent.h>
class b2MouseJoint;

class GeometrySelector : public ClickDragEvent
{
    public:
        GeometrySelector(const Rect& _Rect);
        virtual ~GeometrySelector();
        void start(unsigned char button);
        void mouseMove(int mouseX, int mouseY);
        void buttonUp(int mouseX, int mouseY, unsigned char button);
        void render();
    protected:
    private:
        b2MouseJoint* joint;
};

#endif // GEOMETRYSELECTOR_H
