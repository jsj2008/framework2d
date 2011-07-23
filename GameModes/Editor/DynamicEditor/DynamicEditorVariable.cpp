#include "DynamicEditorVariable.h"
#include <GameModes/Editor/DynamicEditor/DynamicEditorMode.h>
#include <AbstractFactory/FactoryParameters.h>

DynamicEditorVariable::DynamicEditorVariable(CEGUI::Window* _rootWindow, TypeTable* _params)
{
    //ctor
    rootWindow = _rootWindow;
    typeTable = _params;
}

DynamicEditorVariable::~DynamicEditorVariable()
{
    //dtor
}
