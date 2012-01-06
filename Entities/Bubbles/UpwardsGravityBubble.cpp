#include "UpwardsGravityBubble.h"
#include <Box2D/Dynamics/b2Body.h>
#include <Physics/BodyParts/BodyPart.h>

UpwardsGravityBubble::UpwardsGravityBubble()

{
    //ctor
}

UpwardsGravityBubble::~UpwardsGravityBubble()
{
    //dtor
}

void UpwardsGravityBubble::affectBody(BodyPart* _body, Vec2f directionTo)
{
    _body->applyLinearImpulse(Vec2f(0.0,-50), _body->getPosition());
}
