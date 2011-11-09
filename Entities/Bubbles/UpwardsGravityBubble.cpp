#include "UpwardsGravityBubble.h"
#include <Box2D/Dynamics/b2Body.h>
#include <Physics/Body.h>

UpwardsGravityBubble::UpwardsGravityBubble(Skin* _skin)
:Bubble(_skin)
{
    //ctor
}

UpwardsGravityBubble::~UpwardsGravityBubble()
{
    //dtor
}

void UpwardsGravityBubble::affectBody(Body* body, Vec2f directionTo)
{
    body->applyLinearImpulse(Vec2f(0.0,-50), body->getPosition());
}
