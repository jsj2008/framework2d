#include "UpwardsGravityBubble.h"
#include <Box2D/Dynamics/b2Body.h>

UpwardsGravityBubble::UpwardsGravityBubble()
{
    //ctor
}

UpwardsGravityBubble::~UpwardsGravityBubble()
{
    //dtor
}

void UpwardsGravityBubble::affectBody(b2Body* body, Vec2f directionTo)
{
    body->ApplyLinearImpulse(Vec2f(0.0,-50), body->GetWorldCenter());
}
