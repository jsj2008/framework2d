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
























