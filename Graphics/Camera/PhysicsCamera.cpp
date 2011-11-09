#include "PhysicsCamera.h"
#include <Physics/Body.h>
#include <Graphics/GraphicsManager.h>

PhysicsCamera::PhysicsCamera(Body* _body)
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
    Vec2f center = body->getPosition();

    translation.x = -center.x + xView;
    translation.y = -center.y + yView;
}

void PhysicsCamera::activate()
{
    /*Entity* entity = (Entity*)body->GetUserData();
    entity->*/
}
