#include "CharacterController.h"

CharacterController::CharacterController(AIEntity* _entity, unsigned char _booleanButtonsSize, const char** _booleanButtonsNames)
{
    //ctor
    entity = _entity;
    booleanButtonsSize = _booleanButtonsSize;
    booleanButtonsNames = _booleanButtonsNames;
}

CharacterController::~CharacterController()
{
    //dtor
}
