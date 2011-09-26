#include "WheelCharacterController.h"
#include <Entities/AIEntity.h>
#include <Box2D/Box2D.h>
#include <Physics/PhysicsManager.h>

#define WALK_SPEED properties->walkSpeed
#define JUMP_HEIGHT properties->jumpHeight
#define EXTRA_GRAVITY properties->extraGravity
#define JUMP_RECHARGE properties->jumpRecharge
#define FALL_TOLERANCE properties->fallTolerance

WheelCharacterController::WheelCharacterController(AIEntity* _entity, Properties* _properties)
:CharacterController(_entity)
{
    //ctor
    wheel = nullptr;
    airbourneCounter = 0;
    jumpCounter = 0;
    properties = _properties;
}

WheelCharacterController::~WheelCharacterController()
{
    //dtor
    wheel->GetBodyB()->GetWorld()->DestroyBody(wheel->GetBodyB());
}

void WheelCharacterController::walkLeft()
{
    wheel->SetMotorSpeed(-WALK_SPEED);
}
void WheelCharacterController::walkRight()
{
    wheel->SetMotorSpeed(WALK_SPEED);
}
void WheelCharacterController::stopWalking()
{
    wheel->SetMotorSpeed(0.0f);
}
void WheelCharacterController::jump()
{
    if (airbourneCounter != FALL_TOLERANCE && jumpCounter == 0)
    {
        entity->getBody()->ApplyLinearImpulse(Vec2f(0,-JUMP_HEIGHT),Vec2f(0,0));
        airbourneCounter = FALL_TOLERANCE;
        jumpCounter = JUMP_RECHARGE;
    }
}
void WheelCharacterController::update()
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
    entity->getBody()->ApplyLinearImpulse(Vec2f(0,EXTRA_GRAVITY),Vec2f(0,0));
}
