#include "DistanceJointEditor.h"
#include <Physics/PhysicsManager.h>
#include <Level/LevelManager.h>
#include <Input/Mouse/SliderBar.h>
#include <Input/InputState.h>

DistanceJointEditor::DistanceJointEditor(FreeCamera* _camera, CheckBox* _collide)
:BaseJointEditor(_camera,_collide)
{
    //ctor
    frequencyHz = new SliderBar(Vec2i(0,460),300,"Frequency 0-30",0.0f);
    dampingRatio = new SliderBar(Vec2i(0,490),300,"Damping ratio 0-1",0.0f);
    mInputState->registerEvent(frequencyHz);
    mInputState->registerEvent(dampingRatio);
}

DistanceJointEditor::~DistanceJointEditor()
{
    //dtor
}

void DistanceJointEditor::createJoint(b2Body* bodyB, Vec2f& localPointB)
{
    b2DistanceJointDef def;
    def.Initialize(bodyA,bodyB,localPointA,localPointB);
	def.bodyA = bodyA;
	def.bodyB = bodyB;
	def.localAnchorA = localPointA;
	def.localAnchorB = localPointB;
	b2Vec2 d = bodyB->GetWorldPoint(localPointB) - bodyA->GetWorldPoint(localPointA);
	def.length = d.Length();
	def.collideConnected = collideConnected();
	def.dampingRatio = dampingRatio->getPosition();
	def.frequencyHz = frequencyHz->getPosition()*30.0f;
    g_LevelManager.addJoint(&def);
}
