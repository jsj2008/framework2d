#include "BaseJointEditor.h"
#include <Graphics/Camera/FreeCamera.h>
#include <Physics/PhysicsManager.h>

BaseJointEditor::BaseJointEditor(FreeCamera* camera)
{
    //ctor
    mCamera = camera;
    camera->activate();
    bodyA = NULL;
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
            if (body == bodyA)
            {
                localPointA = body->GetLocalPoint(point);
            }
            else
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
    return true;
}
