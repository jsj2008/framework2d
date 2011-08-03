#include "DynamicEditorMode.h"
#include <Level/LevelManager.h>
#include <GameModes/Editor/Undo/UndoStack.h>
#include <GameModes/Editor/Undo/Entries/EntityCreateEntry.h>
#include <GameModes/Editor/DynamicEditor.h>

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

void DynamicEditorMode::initEditorMode(std::string _name, CEGUI::Window* _window, DynamicEditor* _editor)
{
    name = _name;
    rootWindow = _window;
    editor = _editor;
}
void DynamicEditorMode::create()
{
    this->finish();
    for (auto i = variables.begin(); i != variables.end(); i++)
    {
        (*i)->finish();
    }
    UndoStack::global().addEntry(new EntityCreateEntry(name,params,editor->getActiveLevel()));
}

void DynamicEditorMode::addPropertyBagVariable(CppFactoryLoader* _loader)
{
    throw -1;
}
