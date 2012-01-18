#include "BaseJointEditor.h"
#include <Graphics/Camera/FreeCamera.h>
#include <Physics/PhysicsManager.h>
#include <GameModes/Editor/EditorMode.h>
#include <Box2D/Box2D.h>

BaseJointEditor::BaseJointEditor(FreeCamera* camera, EditorMode* _editorMode)
{
    //ctor
    mCamera = camera;
    camera->activate();
    bodyA = nullptr;
    editorMode = _editorMode;
}

BaseJointEditor::~BaseJointEditor()
{
    //dtor
}

void BaseJointEditor::click(Vec2i mouse, unsigned char button)
{
    Vec2f point = mouse.ScreenToWorldSpace();
    b2Body* body = editorMode->getActiveWorld()->select(point);
    if (body != nullptr)
    {
        if (bodyA == nullptr)
        {
            bodyA = body;
            localPointA = body->GetLocalPoint(point);
        }
        else
        {
            if (body == bodyA)
            {
                localPointA = body->GetLocalPoint(point);
            }
            else
            {
                Vec2f localPointB = body->GetLocalPoint(point);
                createJoint(body,localPointB);
                bodyA = nullptr;
            }
        }
    }
}

bool BaseJointEditor::collideConnected()
{
    return true;
}
