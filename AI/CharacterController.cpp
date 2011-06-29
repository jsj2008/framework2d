#include "CharacterController.h"
#include <Entities/AIEntity.h>
#include <Box2D/Box2D.h>

#define WALK_SPEED 20.0f
#define JUMP_HEIGHT 50.0f
#define EXTRA_GRAVITY 0.5
#define JUMP_RECHARGE 5
#define FALL_TOLERANCE 3

CharacterController::CharacterController(AIEntity* _entity)
{
    //ctor
    entity = _entity;
    wheel = nullptr;
    airbourneCounter = 0;
    jumpCounter = 0;
}

CharacterController::~CharacterController()
{
    //dtor
}

void CharacterController::walkLeft()
{
    wheel->SetMotorSpeed(-WALK_SPEED);
}
void CharacterController::walkRight()
{
    wheel->SetMotorSpeed(WALK_SPEED);
}
void CharacterController::stopWalking()
{
    wheel->SetMotorSpeed(0.0f);
}
void CharacterController::jump()
{
    if (airbourneCounter != FALL_TOLERANCE && jumpCounter == 0)
    {
        entity->mBody->ApplyLinearImpulse(Vec2f(0,-JUMP_HEIGHT),Vec2f(0,0));
        airbourneCounter = FALL_TOLERANCE;
        jumpCounter = JUMP_RECHARGE;
    }
}
void CharacterController::update()
{
    bool colliding;
    if (wheel->GetBodyB()->GetContactList() == nullptr)
    {
        colliding = false;
    }
    else
    for (b2ContactEdge* edge = wheel->GetBodyB()->GetContactList(); edge != nullptr; edge = edge->next)
    {
        b2Contact* contact = edge->contact;
        if (contact->IsTouching())
        {
            colliding = true;
            break;
        }
    }
    if (!colliding)
    {
        if (airbourneCounter != FALL_TOLERANCE)
        {
            airbourneCounter++;
        }
    }
    else
    {
        airbourneCounter = 0;
    }
    if (jumpCounter != 0)
    {
        jumpCounter--;
    }
    entity->mBody->ApplyLinearImpulse(Vec2f(0,EXTRA_GRAVITY),Vec2f(0,0));
}
