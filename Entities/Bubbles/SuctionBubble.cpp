#include "SuctionBubble.h"
#include <Box2D/Dynamics/b2Body.h>
#include <Physics/Body.h>

SuctionBubble::SuctionBubble(Skin* _skin)
:Bubble(_skin)
{
    //ctor
}

SuctionBubble::~SuctionBubble()
{
    //dtor
}


void SuctionBubble::affectBody(Body* body, Vec2f directionTo)
{
    body->applyLinearImpulse(directionTo,body->getPosition());
}
