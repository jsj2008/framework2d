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
    float x = startXPos + g_GraphicsManager.getViewX();
    float y = startYPos + g_GraphicsManager.getViewY();
    b2Vec2 point(x/g_GraphicsManager.getPixelsPerMeter(),y/g_GraphicsManager.getPixelsPerMeter());
    b2Body* body = g_PhysicsManager.select(point);
    if (body != NULL)
    {
        if (button == 1)
        {
            joint = g_PhysicsManager.createJoint(body,point);
        }
        else
        {
            g_LevelManager.removeBody(body);
        }
    }
}
void GeometrySelector::mouseMove(int mouseX, int mouseY)
{
    if (joint != NULL)
    {
        float x = mouseX + g_GraphicsManager.getViewX();
        float y = mouseY + g_GraphicsManager.getViewY();
        b2Vec2 point(x/g_GraphicsManager.getPixelsPerMeter(),y/g_GraphicsManager.getPixelsPerMeter());
        joint->SetTarget(point);
        b2Body* body = joint->GetBodyB();
        body->SetAwake(true);
        assert(joint->IsActive());
        assert(body->GetType() == b2_dynamicBody);
        b2Vec2 position = body->GetWorldCenter();
    }
}
void GeometrySelector::buttonUp(int mouseX, int mouseY, unsigned char button)
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




















