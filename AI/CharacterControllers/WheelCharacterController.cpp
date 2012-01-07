#include "WheelCharacterController.h"
#include <Entities/AIEntity.h>
#include <Physics/BodyParts/JointBodyPart.h>
#include <Physics/PhysicsManager.h>

#define WALK_SPEED properties->walkSpeed
#define JUMP_HEIGHT properties->jumpHeight
#define EXTRA_GRAVITY properties->extraGravity
#define JUMP_RECHARGE properties->jumpRecharge
#define FALL_TOLERANCE properties->fallTolerance

#define BOOLEAN_CONTROLS_SIZE 3
const char* staticBooleanControlNames[BOOLEAN_CONTROLS_SIZE] =
{
    "MoveLeft",
    "MoveRight",
    "Jump",
};
WheelCharacterController::WheelCharacterController(JointBodyPart* _joint, Properties* _properties)
:CharacterController(BOOLEAN_CONTROLS_SIZE, staticBooleanControlNames)
{
    //ctor
    airbourneCounter = 0;
    jumpCounter = 0;
    properties = _properties;
    joint = _joint;
}

WheelCharacterController::~WheelCharacterController()
{
    //dtor
    delete joint;
}

void WheelCharacterController::booleanControls(int _button, bool _pressed)
{
    if (_pressed)
    {
        booleanControlStart(_button);
    }
    else
    {
        booleanControlEnd(_button);
    }
}
void WheelCharacterController::booleanControlStart(int _button)
{
    switch (_button)
    {
        case 0:
        {
            walkLeft();
            break;
        }
        case 1:
        {
            walkRight();
            break;
        }
        case 2:
        {
            break;
        }
    }
}
void WheelCharacterController::booleanControlEnd(int _button)
{
    switch (_button)
    {
        case 0:
        {
            stopWalking();
            break;
        }
        case 1:
        {
            stopWalking();
            break;
        }
        case 2:
        {
            jump();
            break;
        }
    }
}
void WheelCharacterController::walkLeft()
{
    joint->setMotorSpeed(-WALK_SPEED);
}
void WheelCharacterController::walkRight()
{
    joint->setMotorSpeed(WALK_SPEED);
}
void WheelCharacterController::stopWalking()
{
    joint->setMotorSpeed(0.0f);
}
void WheelCharacterController::jump()
{
    if (airbourneCounter != FALL_TOLERANCE && jumpCounter == 0)
    {
        entity->getRootBody()->applyLinearImpulse(Vec2f(0,-JUMP_HEIGHT),Vec2f(0,0));
        airbourneCounter = FALL_TOLERANCE;
        jumpCounter = JUMP_RECHARGE;
    }
    //entity->getBody()->ApplyLinearImpulse(Vec2f(0,-JUMP_HEIGHT*0.5f),Vec2f(0,0));
}
void WheelCharacterController::update()
{

    /*bool colliding;
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
    entity->getRootBody()->applyLinearImpulse(Vec2f(0,EXTRA_GRAVITY),Vec2f(0,0));*/
}

