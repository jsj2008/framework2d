#include "DistanceJointEditor.h"
#include <Physics/PhysicsManager.h>
#include <Level/Level.h>
#include <GameModes/Editor/EditorMode.h>
#include <CEGUI/CEGUI.h>

DistanceJointEditor::DistanceJointEditor(FreeCamera* _camera, EditorMode* _editorMode)
:BaseJointEditor(_camera, _editorMode)
{
    //ctor
}

DistanceJointEditor::~DistanceJointEditor()
{
    //dtor
}

void DistanceJointEditor::init()
{
    frequencyHz = (CEGUI::Slider*)CEGUI::System::getSingleton().getGUISheet()->getChildRecursive("DistanceJoints/Frequency");
    dampingRatio = (CEGUI::Slider*)CEGUI::System::getSingleton().getGUISheet()->getChildRecursive("DistanceJoints/Dampingratio");
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
	def.dampingRatio = dampingRatio->getCurrentValue();
	def.frequencyHz = frequencyHz->getCurrentValue();
    //editorMode->getActiveLevel()->addJoint(&def);
}
