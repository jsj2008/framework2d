#include "CharacterController.h"

CharacterController::CharacterController(unsigned char _booleanButtonsSize, const char** _booleanButtonsNames)
{
    //ctor
    entity = nullptr;
    booleanButtonsSize = _booleanButtonsSize;
    booleanButtonsNames = _booleanButtonsNames;
}

CharacterController::~CharacterController()
{
    //dtor
}

void CharacterController::registerActions(GameObjectType* _type)
{

}

void CharacterController::setAIEntity(AIEntity* _entity)
{
    assert(!entity);
    entity = _entity;
}
