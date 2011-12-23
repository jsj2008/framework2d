#include "DynamicEditorMode.h"
#include <Level/LevelEntity.h>
#include <GameModes/Editor/Undo/UndoStack.h>
#include <GameModes/Editor/Undo/Entries/EntityCreateEntry.h>
#include <GameModes/Editor/DynamicEditor.h>
#include <GameModes/Editor/DynamicEditor/EntityList.h>

DynamicEditorMode::DynamicEditorMode(CEGUI::Window* _rootWindow, FactoryParameters* _params)
:DynamicEditorVariable(_params->getTypeTable(),"")
{
    //ctor
    params = _params;
    rootWindow = _rootWindow;
}

DynamicEditorMode::~DynamicEditorMode()
{
    //dtor
}

void DynamicEditorMode::initEditorMode(std::string _name, DynamicEditor* _editor)
{
    name = _name;
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
        LevelEntity* entity = new LevelEntity(editor->getEntityList(), params, name);
        //entry = new EntityCreateEntry(name,name,params,editor->getActiveLevel());
        entry = new EntityCreateEntry(entity, editor->getActiveLevel());
        UndoStack::global().addEntry(entry);
    }
    else
    {
        std::string nameInQuotes("\"");
        nameInQuotes = nameInQuotes + string + '"';
        LevelEntity* entity = new LevelEntity(editor->getEntityList(), params, name);
        //entry = new EntityCreateEntry(name,nameInQuotes,params,editor->getActiveLevel());
        entry = new EntityCreateEntry(entity, editor->getActiveLevel());
        UndoStack::global().addEntry(entry);
        params->remove("name");
    }
    //editor->getEntityList()->addEntity(entry->getEntity(), name);
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
void DynamicEditorMode::addVariable(const std::string& _name, DynamicEditorVariable* _variable)
{
    variables.push_back(_variable);
}





















