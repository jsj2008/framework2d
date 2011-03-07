#ifndef DISTANCEJOINTEDITOR_H
#define DISTANCEJOINTEDITOR_H

#include <GameModes/Editor/Joints/BaseJointEditor.h>
namespace CEGUI
{
    class Slider;
}

class DistanceJointEditor : public BaseJointEditor
{
    public:
        DistanceJointEditor(FreeCamera* _camera);
        virtual ~DistanceJointEditor();
        void init();
    protected:
    private:
        void createJoint(b2Body* bodyB, Vec2f& localPointB);
        CEGUI::Slider* dampingRatio;
        CEGUI::Slider* frequencyHz;
};

#endif // DISTANCEJOINTEDITOR_H
