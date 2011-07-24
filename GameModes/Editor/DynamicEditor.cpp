#include "DynamicEditor.h"
#include <Graphics/Camera/FreeCamera.h>
#include <AbstractFactory/AbstractFactories.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Entities/Entity.h>
#include <Physics/PhysicsManager.h>
#include <GameModes/Editor/DynamicEditor/AllDynamicEditorVariableTypes.h>
#include <GameModes/Editor/DynamicEditor/AllDynamicEditorModes.h>
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
        DynamicEditorVariable* editorVar = (*i)->createVariable(editorMode->getWindow(),params->getTypeTable(), _factoryName);
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

class TextEditBoxFactory : public DynamicEditor::VariableFactory
{
    public:
        TextEditBoxFactory(const std::string& _name, const std::string& _defaultValue){name = _name;defaultValue = _defaultValue;}
        DynamicEditorVariable* createVariable(CEGUI::Window* _rootWindow, TypeTable* _params, const std::string& _factoryName){return new TextEditBox(_rootWindow,_params,name,defaultValue,_factoryName);}
    private:
        std::string name, defaultValue;
};
DynamicEditor::DynamicEditor(FreeCamera* camera)
:editorModes
({
    {{"position","dimensions"}, new DynamicEditor::DerivedModeFactory<BoxDragMode>()},
    {{"points"}, new DynamicEditor::DerivedModeFactory<PointGeometryMode>()},
    {{"position"}, new DynamicEditor::DerivedModeFactory<ClickPlaceMode>()},
}),
editorVariables
({
    {"material", new TextEditBoxFactory("material","StaticSkinFactory")},
})
{
    //ctor
    camera->activate();
    mCamera = camera;
    instanceTab = createTabControl("Entities");
    typeTab = createTabControl("EntityTypes");
    Events::global().registerListener(this);
}

DynamicEditor::~DynamicEditor()
{
    //dtor
    instanceTab->getParent()->destroy();
    typeTab->getParent()->destroy();
    Events::global().unregisterListener(this);
}


bool DynamicEditor::trigger(FactoryTypeRegisterEvent<Entity>* event)
{
    return true;
}
#include <iostream>
std::vector<b2Body*> deadBodies;
void DynamicEditor::init()
{
    for (unsigned int i = 0; i < FactoryTypeRegisterEvent<Entity>::factoryNames.size(); i++)
    {
        std::string name = FactoryTypeRegisterEvent<Entity>::factoryNames[i];
        if (name != "AIEntityFactory")
        {
            DynamicEditor::EditorFactory* factory = searchExistingFactoryInstances(name, true);
            if (factory != nullptr)
            {
                editorFactories[name] = factory;
                activeEditor = factory->createEditor(instanceTab, name);
                factoryInstances.push_back(activeEditor);
                instanceTab->setSelectedTabAtIndex(instanceTab->getTabCount()-1);
            }
        }
    }

    for (unsigned int i = 0; i < deadBodies.size(); i++)
        g_PhysicsManager.destroyBody(deadBodies[i]);
    deadBodies.clear();
    FactoryTypeRegisterEvent<Entity>::factoryNames.clear();
}

DynamicEditor::EditorFactory* DynamicEditor::searchExistingFactoryInstances(const std::string& factoryName, bool _createType)
{
    AbstractFactoryBase<Entity>* factory = AbstractFactories::global().getFactory<Entity>(factoryName);
    EditorFactoryType* editor = nullptr;
    {
        FactoryParameters parameters(true);
        deadBodies.push_back(factory->use(&parameters)->mBody);
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
            if (matches == editorMode->first.size())
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
                //break;
                goto MATCH_FOUND;
            }
            /// else matchedStrings.clear(); - Not necessary
        }
    }
    return nullptr;
MATCH_FOUND:
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
                editor->addTypeVariable(variable->second->createVariable(page, params->getTypeTable(),factoryName));
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
    factoryInstances[instanceTab->getSelectedTabIndex()]->buttonDown(mouse,button);
}
void DynamicEditor::mouseMove(Vec2i mouse)
{
    factoryInstances[instanceTab->getSelectedTabIndex()]->mouseMove(mouse);
}
void DynamicEditor::buttonUp(Vec2i mouse, unsigned char button)
{
    factoryInstances[instanceTab->getSelectedTabIndex()]->buttonUp(mouse,button);
}
void DynamicEditor::render()
{
    factoryInstances[instanceTab->getSelectedTabIndex()]->render();
}

bool DynamicEditor::FactoryGetList::trigger(FactoryGetEvent* event)
{
    factories.insert(event->getName());
    return true;
}
bool DynamicEditor::FactoryUseList::trigger(FactoryEvent<b2Body>* event)
{
    factories.push_back(event->get());
    return true;
}
