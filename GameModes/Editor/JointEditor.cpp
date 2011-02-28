#include "JointEditor.h"
#include <Graphics/Camera/FreeCamera.h>
#include <Input/Mouse/SelectionBox.h>
#include <Input/Mouse/SliderBar.h>
#include <Physics/PhysicsManager.h>
#include <Level/LevelManager.h>

JointEditor::JointEditor(FreeCamera* camera, const Rect& _Rect)
:ClickReleaseEvent(_Rect)
{
    //ctor
    bodyA = NULL;
    mCamera = camera;
    mInputState = new InputState;
    camera->registerWithInputState(mInputState);
    Rect fullScreen(0,0,10000,10000);
    mInputState->registerEvent(this);
    Rect rect(0,400,300,450);
    SelectionBox* selectionBox = new SelectionBox(rect,{"Distance joint"});
    mInputState->registerEvent(selectionBox);
    mInputState->registerEvent(new SliderBar(Vec2i(0,450),300,"Arp"));
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
            localPointA = body->GetLocalPoint(point);
        }
        else
        {
            if (body != bodyA)
            {
                Vec2f localPointB = body->GetLocalPoint(point);
                createJoint(body,localPointB);
                bodyA = NULL;
            }
        }
    }
}

void JointEditor::createJoint(b2Body* bodyB, Vec2f& localPointB)
{
    b2DistanceJointDef def;
    def.Initialize(bodyA,bodyB,localPointA,localPointB);
	def.bodyA = bodyA;
	def.bodyB = bodyB;
	def.localAnchorA = localPointA;
	def.localAnchorB = localPointB;
	b2Vec2 d = bodyB->GetWorldPoint(localPointB) - bodyA->GetWorldPoint(localPointA);
	def.length = d.Length();
    g_LevelManager.addJoint(&def);
}
