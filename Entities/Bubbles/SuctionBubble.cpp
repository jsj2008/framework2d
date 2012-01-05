#include "SuctionBubble.h"
#include <Box2D/Dynamics/b2Body.h>
#include <Physics/BodyPart.h>

SuctionBubble::SuctionBubble()

{
    //ctor
}

SuctionBubble::~SuctionBubble()
{
    //dtor
}


void SuctionBubble::affectBody(BodyPart* _body, Vec2f directionTo)
{
    _body->applyLinearImpulse(directionTo,_body->getPosition());
}
