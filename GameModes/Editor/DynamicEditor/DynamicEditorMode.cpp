#include "DynamicEditorMode.h"
#include <Level/LevelManager.h>

DynamicEditorMode::DynamicEditorMode(DynamicEditorMode* _editor, FactoryParameters* _params)
:DynamicEditorVariable(_editor, _params)
{
    //ctor
}

DynamicEditorMode::~DynamicEditorMode()
{
    //dtor
}

void DynamicEditorMode::initEditorMode(std::string _name, CEGUI::Window* _window)
{
    name = _name;
    window = _window;
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

void DynamicEditorMode::addChildWindow(CEGUI::Window* _window)
{
    window->addChildWindow(_window);
}
