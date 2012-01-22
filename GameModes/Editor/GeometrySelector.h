#ifndef GEOMETRYSELECTOR_H
#define GEOMETRYSELECTOR_H

#include <unordered_set>
#include <Input/Mouse/ClickDragEvent.h>
#include <GameModes/GameMode.h>
class b2MouseJoint;
class FreeCamera;
class EditorMode;

class GeometrySelector : public GameMode, public ClickDragEvent
{
    public:
        GeometrySelector(FreeCamera* camera, EditorMode* _editorMode);
        virtual ~GeometrySelector();
        void start(unsigned char button);
        void mouseMove(Vec2i mouse);
        void buttonUp(Vec2i mouse, unsigned char button);
        void render();
    protected:
    private:
        bool v_Update(){return true;}  // FIXME
        b2MouseJoint* mouseJoint;
        unsigned int bodyHealth;
        std::unordered_set<b2MouseJoint*> activeMouseJoints;
        void drawMouseJoints();
        EditorMode* editorMode;
};

#endif // GEOMETRYSELECTOR_H
