#include "DynamicEditorVariable.h"
#include <GameModes/Editor/DynamicEditor/DynamicEditorMode.h>
#include <AbstractFactory/FactoryParameters.h>

DynamicEditorVariable::DynamicEditorVariable(CEGUI::Window* _rootWindow, TypeTable* _params, const std::string& _factoryName)
{
    //ctor
    rootWindow = _rootWindow;
    typeTable = _params;
    factoryName = _factoryName;
}

DynamicEditorVariable::~DynamicEditorVariable()
{
    //dtor
}
