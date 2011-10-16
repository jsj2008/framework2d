#include "DynamicEditorVariable.h"
#include <GameModes/Editor/DynamicEditor/DynamicEditorMode.h>
#include <AbstractFactory/FactoryParameters.h>

DynamicEditorVariable::DynamicEditorVariable(TypeTable* _params, const std::string& _name)
{
    //ctor
    typeTable = _params;
    name = _name;
}

DynamicEditorVariable::~DynamicEditorVariable()
{
    //dtor
}
