#include "PhysicsCamera.h"
#include <Box2D/Dynamics/b2Body.h>
#include <Graphics/GraphicsManager.h>

PhysicsCamera::PhysicsCamera(b2Body* _body)
{
    //ctor
    body = _body;
    scale = 15.0f;
}

PhysicsCamera::~PhysicsCamera()
{
    //dtor
}

void PhysicsCamera::updateTransform(int xRes, int yRes)
{
    float xView = xRes / (2.0f * scale);
    float yView = yRes / (2.0f * scale);
    b2Vec2 center = body->GetWorldCenter();

    xTrans = -center.x + xView;
    yTrans = -center.y + yView;
}
