#include "JointEditor.h"
#include <Physics/PhysicsManager.h>
#include <Level/LevelManager.h>

JointEditor::JointEditor(const Rect& _Rect)
:ClickReleaseEvent(_Rect)
{
    //ctor
    bodyA = NULL;
}

JointEditor::~JointEditor()
{
    //dtor
}

void JointEditor::click(Vec2i mouse, unsigned char button)
{
    Vec2f point = mouse.ScreenToWorldSpace();
    b2Body* body = g_PhysicsManager.select(point);
    if (body != NULL)
    {
        if (bodyA == NULL)
        {
            bodyA = body;
            worldPointA = point;
        }
        else
        {
            if (body != bodyA)
            {
                createJoint(body,point);
                bodyA = NULL;
            }
        }
    }
}

void JointEditor::createJoint(b2Body* bodyB, Vec2f& worldPointB)
{
    b2DistanceJointDef def;
    def.Initialize(bodyA,bodyB,worldPointA,worldPointB);
    g_LevelManager.addJoint(&def);
}
