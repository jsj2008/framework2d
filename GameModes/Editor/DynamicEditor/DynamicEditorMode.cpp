#include "DynamicEditorMode.h"
#include <Level/LevelManager.h>
#include <GameModes/Editor/Undo/UndoStack.h>
#include <GameModes/Editor/Undo/Entries/EntityCreateEntry.h>
#include <GameModes/Editor/DynamicEditor.h>
#include <GameModes/Editor/DynamicEditor/EntityList.h>

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
    rootWindow->getChild(_name+"Tab/DeleteButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(&DynamicEditorMode::destroySelf,this));
}
void DynamicEditorMode::create()
{
    this->finish();
    for (auto i = variables.begin(); i != variables.end(); i++)
    {
        (*i)->finish();
    }
    const std::string& string = params->get<std::string>("name", "");
    EntityCreateEntry* entry = nullptr;
    if (string == "")
    {
        entry = new EntityCreateEntry(name,name,params,editor->getActiveLevel());
        UndoStack::global().addEntry(entry);
    }
    else
    {
        std::string nameInQuotes("\"");
        nameInQuotes = nameInQuotes + string + '"';
        entry = new EntityCreateEntry(name,nameInQuotes,params,editor->getActiveLevel());
        UndoStack::global().addEntry(entry);
        params->remove("name");
    }
    editor->getEntityList()->addEntity(entry->getEntity(), name);// continue working here
}

void DynamicEditorMode::addPropertyBagVariable(CppFactoryLoader* _loader)
{
    throw -1;
}

bool DynamicEditorMode::destroySelf(const CEGUI::EventArgs&)
{
    delete params;
    params = nullptr;
    static_cast<CEGUI::TabControl*>(rootWindow->getParent()->getParent())->removeTab(rootWindow->getName());
    delete this;
    return false;
}
