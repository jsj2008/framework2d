#ifndef GEOMETRYSELECTOR_H
#define GEOMETRYSELECTOR_H

#include <unordered_set>
#include <Input/Mouse/ClickDragEvent.h>
#include <GameModes/GameMode.h>
class b2MouseJoint;
class FreeCamera;

class GeometrySelector : public GameMode, public ClickDragEvent
{
    public:
        GeometrySelector(FreeCamera* camera);
        virtual ~GeometrySelector();
        void start(unsigned char button);
        void mouseMove(Vec2i mouse);
        void buttonUp(Vec2i mouse, unsigned char button);
        void render();
    protected:
    private:
        b2MouseJoint* mouseJoint;
        std::unordered_set<b2MouseJoint*> activeMouseJoints;
        void drawMouseJoints();
};

#endif // GEOMETRYSELECTOR_H
