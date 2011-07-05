#include "DynamicEditorVariable.h"
#include <GameModes/Editor/DynamicEditor.h>
#include <AbstractFactory/FactoryParameters.h>

DynamicEditorVariable::DynamicEditorVariable()
{
    //ctor
}

DynamicEditorVariable::~DynamicEditorVariable()
{
    //dtor
}

void DynamicEditorVariable::initEditorVariable(DynamicEditor* _editor, FactoryParameters* _params)
{
    editor = _editor;
    params = _params;
}
