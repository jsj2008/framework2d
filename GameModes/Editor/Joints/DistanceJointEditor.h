#ifndef DISTANCEJOINTEDITOR_H
#define DISTANCEJOINTEDITOR_H

#include <GameModes/Editor/Joints/BaseJointEditor.h>
class SliderBar;

class DistanceJointEditor : public BaseJointEditor
{
    public:
        DistanceJointEditor(FreeCamera* _camera, CheckBox* _collide);
        virtual ~DistanceJointEditor();
    protected:
    private:
        void createJoint(b2Body* bodyB, Vec2f& localPointB);
        SliderBar* dampingRatio;
        SliderBar* frequencyHz;
};

#endif // DISTANCEJOINTEDITOR_H
