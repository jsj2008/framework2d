#include "DynamicEditor.h"
#include <Graphics/Camera/FreeCamera.h>
#include <AbstractFactory/AbstractFactories.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Entities/Entity.h>
#include <Physics/PhysicsManager.h>
#include <GameModes/Editor/DynamicEditor/AllDynamicEditorVariableTypes.h>
#include <AbstractFactory/FactoryLoaders/TextFileFactoryLoader.h>
#include <Events/Events.h>
std::vector<std::pair<std::vector<std::string>,DynamicEditor::ModeFactory*>> DynamicEditor::editorModes
({
    {
        {"position","dimensions"}, new DynamicEditor::DerivedModeFactory<BoxDragVariable>(),
    }
 });
std::unordered_map<std::string, DynamicEditor::VariableFactory*> DynamicEditor::editorVariables
({
    {
        "StaticSkinFactory", new DynamicEditor::DerivedVariableFactory<TextEditBox>()
    }
 });

DynamicEditor::DynamicEditor(FreeCamera* camera)
{
    //ctor
    camera->activate();
    mCamera = camera;
    window = CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("EditMode.layout", "DynamicEditor");
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(window);
}

DynamicEditor::~DynamicEditor()
{
    //dtor
}
#include <iostream>
void DynamicEditor::init()
{
    activeEditor = createEditorMode("CrateFactory");
}

DynamicEditorMode* DynamicEditor::createEditorMode(const std::string& factoryName)
{
    AbstractFactoryBase<Entity>* factory = AbstractFactories::global().getFactory<Entity>(factoryName);
    BoxDragVariable* editor = nullptr;
    CEGUI::TabControl* tab;
    {
        FactoryParameters parameters(true);
        g_PhysicsManager.destroyBody(factory->use(&parameters)->mBody);
        std::vector<std::string> values = parameters.getUndefinedLog(); /// FIXME this could be faster, its stored as a map internally, we could sort it
        for (auto editorMode = editorModes.begin(); editorMode != editorModes.end(); editorMode++)
        {
            unsigned int matches = 0;
            std::vector<std::vector<std::string>::iterator> matchedStrings; /// Keep a track of these so we can delete them in case of a complete match
            for (auto string = editorMode->first.begin(); string != editorMode->first.end(); string++)
            {
                for (auto value = values.begin(); value != values.end(); value++)
                {
                    if (*value == *string)
                    {
                        matches++;
                        matchedStrings.push_back(value);
                        break;
                    }
                }
            }
            if (matches == values.size())
            {
                tab = static_cast<CEGUI::TabControl*>(window->getChild("DynamicEditor/TabControl"));
                CEGUI::Window *page = CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("EditorTab.layout", factoryName);
                page->setProperty("Text",factoryName);
                tab->addTab(page);
                editor = new BoxDragVariable(editor, &params);
                editor->initEditorMode(factoryName, page);
                while (!matchedStrings.empty())
                {
                    values.erase(matchedStrings.back());
                    matchedStrings.pop_back();
                }
                break;
            }
            /// else matchedStrings.clear(); - Not necessary
        }
    }
    {
        TextFileFactoryLoader loader(nullptr, true);
        FactoryGetList getList;
        Events::global().registerListener<FactoryGetEvent>(&getList);
        factory->init(&loader, &AbstractFactories::global());
        Events::global().unregisterListener<FactoryGetEvent>(&getList);
        std::vector<std::string> values = loader.getUndefinedLog();
        for (auto value = getList.getFactories().begin(); value != getList.getFactories().end(); value++)
        {
            auto variable = editorVariables.find(*value);
            if (variable != editorVariables.end())
            {
                DynamicEditorVariable* editorVar = variable->second->createVariable(editor,&params);
                editor->addVariable(editorVar);
            }
        }
    }
    tab->setSelectedTabAtIndex(0);
    CEGUI::EventArgs args;
    activate(args);
    return editor;
}

void DynamicEditor::buttonDown(Vec2i mouse, unsigned char button)
{
    activeEditor->buttonDown(mouse,button);
}
void DynamicEditor::mouseMove(Vec2i mouse)
{
    activeEditor->mouseMove(mouse);
}
void DynamicEditor::buttonUp(Vec2i mouse, unsigned char button)
{
    activeEditor->buttonUp(mouse,button);
}

bool DynamicEditor::FactoryGetList::trigger(FactoryGetEvent* event)
{
    factories.insert(event->getName());
    return true;
}
