#include "DynamicEditorVariable.h"
#include <GameModes/Editor/DynamicEditor/DynamicEditorMode.h>
#include <AbstractFactory/FactoryParameters.h>

DynamicEditorVariable::DynamicEditorVariable(DynamicEditorMode* _editor, FactoryParameters* _params)
{
    //ctor
    editor = _editor;
    params = _params;
}

DynamicEditorVariable::~DynamicEditorVariable()
{
    //dtor
}
