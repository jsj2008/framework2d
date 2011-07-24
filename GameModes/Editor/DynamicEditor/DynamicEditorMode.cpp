#include "DynamicEditorMode.h"
#include <Level/LevelManager.h>

DynamicEditorMode::DynamicEditorMode(FactoryParameters* _params)
:DynamicEditorVariable(nullptr, _params->getTypeTable(),"")
{
    //ctor
    params = _params;
}

DynamicEditorMode::~DynamicEditorMode()
{
    //dtor
}

void DynamicEditorMode::initEditorMode(std::string _name, CEGUI::Window* _window)
{
    name = _name;
    rootWindow = _window;
}
void DynamicEditorMode::create()
{
    this->finish();
    for (auto i = variables.begin(); i != variables.end(); i++)
    {
        (*i)->finish();
    }
    g_LevelManager.addBody(name, params);
}

void DynamicEditorMode::addPropertyBagVariable(CppFactoryLoader* _loader)
{
    throw -1;
}
