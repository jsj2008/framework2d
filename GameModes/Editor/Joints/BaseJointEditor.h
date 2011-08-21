#ifndef BASEJOINTEDITOR_H
#define BASEJOINTEDITOR_H

#include <GameModes/GameMode.h>
#include <Input/Mouse/ClickReleaseEvent.h>
#include <Types/Vec2f.h>
class FreeCamera;
class b2Body;
class EditorMode;

class BaseJointEditor : public GameMode, public ClickReleaseEvent
{
    public:
        BaseJointEditor(FreeCamera* camera, EditorMode* _editorMode);
        virtual ~BaseJointEditor();
        void click(Vec2i mouse, unsigned char button);
        bool update(){return true;}  // FIXME
    protected:
        b2Body* bodyA;
        Vec2f localPointA;
        bool collideConnected();
        EditorMode* editorMode;
    private:
        virtual void createJoint(b2Body* bodyB, Vec2f& localPointB)=0;
};

#endif // BASEJOINTEDITOR_H
