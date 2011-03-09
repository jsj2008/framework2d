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

void PhysicsCamera::updateTransform(Vec2i resolution)
{
    float xView = resolution.x / (2.0f * scale);
    float yView = resolution.y / (2.0f * scale);
    Vec2f center = body->GetWorldCenter();

    translation.x = -center.x + xView;
    translation.y = -center.y + yView;
}

void PhysicsCamera::activate()
{
    /*Entity* entity = (Entity*)body->GetUserData();
    entity->*/
}
