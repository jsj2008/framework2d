#ifndef JOINTEDITOR_H
#define JOINTEDITOR_H

#include <Input/Mouse/ClickReleaseEvent.h>
class b2Body;

class JointEditor : public ClickReleaseEvent
{
    public:
        JointEditor(const Rect& _Rect);
        virtual ~JointEditor();
        void click(Vec2i mouse, unsigned char button);
    protected:
    private:
        b2Body* bodyA;
        Vec2f worldPointA;
        void createJoint(b2Body* bodyB, Vec2f& worldPointB);
};

#endif // JOINTEDITOR_H
