#include "SuctionBubble.h"
#include <Box2D/Dynamics/b2Body.h>

SuctionBubble::SuctionBubble(Skin* _skin)
:Bubble(_skin)
{
    //ctor
}

SuctionBubble::~SuctionBubble()
{
    //dtor
}


void SuctionBubble::affectBody(b2Body* body, Vec2f directionTo)
{
    body->ApplyLinearImpulse(directionTo,body->GetWorldCenter());
}
