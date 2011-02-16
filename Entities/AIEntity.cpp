#include "AIEntity.h"
#include <AI/Brain.h>
#include <Box2D/Box2D.h>

AIEntity::AIEntity(Brain* _Brain)
{
    //ctor
    mBrain = _Brain;
    mBrain->setEntity(this);
}

AIEntity::~AIEntity()
{
    //dtor
}
void AIEntity::update()
{
}
#include <iostream>
#define kWorldGravity   1
#define kJumpImpulse   -0.1*kWorldGravity
#define kPlayerMass   1.0
void AIEntity::jump()
{
    b2Vec2 point(0,0);
    //mBody->ApplyLinearImpulse(b2Vec2(0,-0.000001f),point);
    mBody->ApplyLinearImpulse(b2Vec2(0.0,kJumpImpulse), mBody->GetWorldCenter());
    std::cout << "jumping\n" << point.x << std::endl << point.y;
}
