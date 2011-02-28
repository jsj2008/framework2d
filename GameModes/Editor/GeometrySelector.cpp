#include "GeometrySelector.h"
#include <Graphics/GraphicsManager.h>
#include <Level/LevelManager.h>
#include <Physics/PhysicsManager.h>
#include <Box2D/Common/b2Math.h>

GeometrySelector::GeometrySelector(const Rect& _Rect)
:ClickDragEvent(_Rect)
{
    //ctor
    joint = NULL;
}

GeometrySelector::~GeometrySelector()
{
    //dtor
}

void GeometrySelector::start(unsigned char button)
{
    if (joint != NULL)
    {
        mouseMove(startPos);
        joint = NULL;
    }
    else
    {
        Vec2f point = startPos.ScreenToWorldSpace();
        b2Body* body = g_PhysicsManager.select(point);
        if (body != NULL)
        {
            if (button == 1 && body->GetType() == b2_dynamicBody)
            {
                joint = g_PhysicsManager.createJoint(body,point);
            }
            else
            {
                g_LevelManager.removeBody(body);
            }
        }
    }
}
void GeometrySelector::mouseMove(Vec2i mouse)
{
    if (joint != NULL)
    {
        Vec2f point = mouse.ScreenToWorldSpace();
        joint->SetTarget(point);
        b2Body* body = joint->GetBodyB();
        body->SetAwake(true);
        assert(joint->IsActive());
        Vec2f position = body->GetWorldCenter();
    }
}
void GeometrySelector::buttonUp(Vec2i mouse, unsigned char button)
{
    if (joint != NULL)
    {
        g_PhysicsManager.deleteJoint(joint);
        joint = NULL;
    }
}
void GeometrySelector::render()
{
}




















