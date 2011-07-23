#include "DynamicEditor.h"
#include <Graphics/Camera/FreeCamera.h>
#include <AbstractFactory/AbstractFactories.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Entities/Entity.h>
#include <Physics/PhysicsManager.h>
#include <GameModes/Editor/DynamicEditor/AllDynamicEditorVariableTypes.h>
#include <AbstractFactory/FactoryLoaders/TextFileFactoryLoader.h>
#include <Events/Events.h>
#include <AbstractFactory/FactoryLoaders/CppFactoryLoader.h>

template <typename mode>
DynamicEditorMode* DynamicEditor::DerivedModeFactory<mode>::createMode(FactoryParameters* _params)
{
    return new mode(_params);
}

InputContext* DynamicEditor::EditorFactory::createEditor(CEGUI::TabControl* _tab, std::string _factoryName)
{
    FactoryParameters* params = new FactoryParameters(true);
    DynamicEditorMode* editorMode = factoryType->modeFactory->createMode(params);

    CEGUI::Window *page = CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("EditorTab.layout", _factoryName);
    page->setProperty("Text",_factoryName);
    _tab->addTab(page);

    editorMode->initEditorMode(_factoryName, page);

    for (auto i = factoryType->instanceVariableFactories.begin(); i != factoryType->instanceVariableFactories.end(); i++)
    {
        DynamicEditorVariable* editorVar = (*i)->createVariable(editorMode->getWindow(),params->getTypeTable());
        editorMode->addVariable(editorVar);
    }

    return editorMode;
}
bool DynamicEditor::EditorFactoryType::createButton(const CEGUI::EventArgs& _args)
{
    CppFactoryLoader loader;
    std::string name = instanceNameWidget->getProperty("Text").c_str();
    loader.setName(name);
    loader.setType(factoryTypeName);
    for (auto i = variables.begin(); i != variables.end(); i++)
    {
        (*i)->addPropertyBagVariable(&loader);
    }
    AbstractFactories::global().addFactory<Entity>(&loader);
    editor->editorFactories[name] = editor->searchExistingFactoryInstances(name, false);
    editor->activeEditor = editor->editorFactories[name]->createEditor(editor->instanceTab, name);
    editor->factoryInstances.push_back(editor->activeEditor);
    editor->instanceTab->setSelectedTabAtIndex(editor->instanceTab->getTabCount()-1);
    std::ofstream file ("Resources/EntityFactories.txt", std::ios::app);
    for (auto i = variables.begin(); i != variables.end(); i++)
    {
        (*i)->addPropertyBagVariable(&loader);
    }
    loader.output(&file);
    return true;
}
CEGUI::TabControl* createTabControl(const std::string& _prefix)
{
    CEGUI::Window* window = CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("EditMode.layout", _prefix);
    window->setText(_prefix);
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(window);
    CEGUI::Window* uncastTab = window->getChild(_prefix + "/TabControl");
    assert(dynamic_cast<CEGUI::TabControl*>(uncastTab));
    return static_cast<CEGUI::TabControl*>(uncastTab);
}
DynamicEditor::DynamicEditor(FreeCamera* camera)
:editorModes
({{
    {"position","dimensions"}, new DynamicEditor::DerivedModeFactory<BoxDragMode>(),
}}),
editorVariables
({{
    "material", new DynamicEditor::DerivedVariableFactory<TextEditBox>()
}})
{
    //ctor
    camera->activate();
    mCamera = camera;
    instanceTab = createTabControl("Entities");
    typeTab = createTabControl("EntityTypes");
}

DynamicEditor::~DynamicEditor()
{
    //dtor
    instanceTab->getParent()->destroy();
    typeTab->getParent()->destroy();
}
#include <iostream>
void DynamicEditor::init()
{
    editorFactories["CrateFactory"] = searchExistingFactoryInstances("CrateFactory", true);
    activeEditor = editorFactories["CrateFactory"]->createEditor(instanceTab, "CrateFactory");
    factoryInstances.push_back(activeEditor);
    instanceTab->setSelectedTabAtIndex(instanceTab->getTabCount()-1);
}

DynamicEditor::EditorFactory* DynamicEditor::searchExistingFactoryInstances(const std::string& factoryName, bool _createType)
{
    AbstractFactoryBase<Entity>* factory = AbstractFactories::global().getFactory<Entity>(factoryName);
    EditorFactoryType* editor = nullptr;
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
                editor = new EditorFactoryType(editorMode->second, this, factoryName);
                while (!matchedStrings.empty())
                {
                    values.erase(matchedStrings.back());
                    matchedStrings.pop_back();
                }
                for (auto value = values.begin(); value != values.end(); value++)
                {
                    auto variable = editorVariables.find(*value);
                    if (variable != editorVariables.end())
                    {
                        editor->addInstanceVariableFactory(variable->second);
                    }
                }
                break;
            }
            /// else matchedStrings.clear(); - Not necessary
        }
    }
    if (_createType)
    {
        TextFileFactoryLoader loader(nullptr, true);
        FactoryGetList getList;
        Events::global().registerListener<FactoryGetEvent>(&getList);
        factory->init(&loader, &AbstractFactories::global());
        Events::global().unregisterListener<FactoryGetEvent>(&getList);
        std::vector<std::string> values = loader.getUndefinedLog();
        FactoryParameters* params = new FactoryParameters();
        CEGUI::Window *page = CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("EditorTab.layout", factoryName + "Type");
        for (auto value = values.begin(); value != values.end(); value++)
        {
            auto variable = editorVariables.find(*value);
            if (variable != editorVariables.end())
            {
                editor->addTypeVariable(variable->second->createVariable(page, params->getTypeTable()));
            }
        }
        page->setProperty("Text",factoryName + "Type");
        typeTab->addTab(page);

        CEGUI::Window* button = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button",factoryName + "CreateButton");
        button->setPosition(CEGUI::UVector2(CEGUI::UDim(0.75,0),CEGUI::UDim(0.50,0)));
        button->setSize(CEGUI::UVector2(CEGUI::UDim(0,50),CEGUI::UDim(0,50)));
        button->setText("Create");
        page->addChildWindow(button);

        CEGUI::Window* factoryNameBox = CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("EditBox.layout", factoryName + "InstanceName");
        factoryNameBox->setProperty("Text","EnterEntityName");
        factoryNameBox->setProperty("VerticalAlignment", "Top");
        page->addChildWindow(factoryNameBox);
        editor->setInstanceNameWidget(factoryNameBox);

        button->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::SubscriberSlot(&EditorFactoryType::createButton,editor));
    }
    CEGUI::EventArgs args;
    activate(args);
    return new EditorFactory(editor);
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
