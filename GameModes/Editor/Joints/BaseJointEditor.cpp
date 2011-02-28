#include "BaseJointEditor.h"
#include <Input/InputState.h>
#include <Graphics/Camera/FreeCamera.h>
#include <Physics/PhysicsManager.h>
#include <Input/Mouse/CheckBox.h>

BaseJointEditor::BaseJointEditor(FreeCamera* camera, CheckBox* _collide)
:ClickReleaseEvent(Rect(0,0,10000,10000))
{
    //ctor
    mCamera = camera;
    mInputState = new InputState;
    camera->registerWithInputState(mInputState);
    mInputState->registerEvent(this);
    bodyA = NULL;
    collide = _collide;
    mInputState->registerEvent(collide);
}

BaseJointEditor::~BaseJointEditor()
{
    //dtor
}

void BaseJointEditor::click(Vec2i mouse, unsigned char button)
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

bool BaseJointEditor::collideConnected()
{
    return collide->getChecked();
}
