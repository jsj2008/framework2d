#include "DynamicEditor.h"
#include <Graphics/Camera/FreeCamera.h>
#include <AbstractFactory/AbstractFactories.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Entities/Entity.h>
#include <Physics/PhysicsManager.h>
#include <GameModes/Editor/DynamicEditor/AllDynamicEditorVariableTypes.h>
#include <GameModes/Editor/DynamicEditor/AllDynamicEditorModes.h>
#include <AbstractFactory/FactoryLoaders/TextFileFactoryLoader.h>
#include <GameModes/Editor/EditorMode.h>
#include <Events/Events.h>
#include <AbstractFactory/FactoryLoaders/CppFactoryLoader.h>
#include <GameModes/Editor/DynamicEditor/EntityList.h>

template <typename mode>
DynamicEditorMode* DynamicEditor::DerivedModeFactory<mode>::createMode(CEGUI::Window* _window, FactoryParameters* _params)
{
    return new mode(_window, _params);
}

InputContext* DynamicEditor::EditorFactoryType::createEditor(CEGUI::TabControl* _tab, std::string _factoryName, std::string _typeName, DynamicEditor* _editor)
{
    CEGUI::Window* page = CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("EntityInstanceTab.layout", _factoryName);

    FactoryParameters* params = new FactoryParameters(true);
    DynamicEditorMode* editorMode = modeFactory->createMode(page, params);

    CEGUI::Window* typeNameDisplay = page->getChild(_factoryName + "Tab/EntityTypeName");
    typeNameDisplay->appendText(_typeName);
    page->setProperty("Text",_factoryName);
    _tab->addTab(page);
    page->setUserData(editorMode);

    editorMode->initEditorMode(_factoryName, _editor);

    float uiElementTop = 0.0f;
    for (auto i = instanceVariableFactories.begin(); i != instanceVariableFactories.end(); i++)
    {
        DynamicEditorVariable* editorVar = (*i)->createVariable(editorMode->getWindow(),params->getTypeTable(), _factoryName, &uiElementTop);
        editorMode->addVariable((*i)->getName(), editorVar);
    }

    return editorMode;
}
std::vector<Entity*> deadBodies; /// FIXME
bool DynamicEditor::EditorFactoryType::createButton(const CEGUI::EventArgs& _args)
{
    CppFactoryLoader* __loader = nullptr; /// FIXME
    CppFactoryLoader& loader = *__loader;
    std::string name = instanceNameWidget->getProperty("Text").c_str();
    loader.setName(name);
    loader.setType(factoryTypeName);
    for (auto i = variables.begin(); i != variables.end(); i++)
    {
        DynamicEditorVariable* variable = *i;
        variable->addPropertyBagVariable(&loader);
    }
    ///AbstractFactories::global().addFactory<Entity>(&loader); FIXME
    for (unsigned int i = 0; i < deadBodies.size(); i++)
        delete deadBodies[i];
    deadBodies.clear();
    editor->activeEditor = createEditor(editor->instanceTab, name, factoryTypeName, editor);
    editor->instanceTab->setSelectedTabAtIndex(editor->instanceTab->getTabCount()-1);
    /*for (auto i = variables.begin(); i != variables.end(); i++)
    {
        (*i)->addPropertyBagVariable(&loader);
    }*/
    loader.output();
    return true;
}
CEGUI::TabControl* getTabControl(const std::string& _prefix)
{
    CEGUI::Window* window = CEGUI::System::getSingletonPtr()->getGUISheet()->getChild(_prefix);
    //CEGUI::System::getSingleton().getGUISheet()->addChildWindow(window);
    CEGUI::Window* uncastTab = window->getChild(_prefix + "/TabControl");
    assert(dynamic_cast<CEGUI::TabControl*>(uncastTab));
    return static_cast<CEGUI::TabControl*>(uncastTab);
}

class NameVariableController: public DynamicEditorVariable
{
    public:
        NameVariableController(CEGUI::Window* _entityName, TypeTable* _params, float* _uiElementTop)
        :DynamicEditorVariable(_params, "name")
        {
            entityName = _entityName;
        }
        void finish()
        {
            std::string string = entityName->getProperty("Text").c_str();
            if (string != "")
            {
                typeTable->addValue<std::string>(name, string.c_str());
            }
        }
        void addPropertyBagVariable(CppFactoryLoader* _loader)
        {
            std::string string = entityName->getProperty("Text").c_str();
            if (string != "")
            {
                _loader->addValue<std::string>(name, string.c_str());
            }
        }
    private:
        CEGUI::Window* entityName;
};

class NameVariableControllerFactory : public DynamicEditor::VariableFactory
{
    public:
        NameVariableControllerFactory(const std::string& _name, CEGUI::Window* _nameEditBox):VariableFactory(_name){nameEditBox = _nameEditBox;}
        DynamicEditorVariable* createVariable(CEGUI::Window* _rootWindow,
            TypeTable* _params, const std::string& _factoryName, float* _uiElementTop){return new NameVariableController(nameEditBox,_params, _uiElementTop);}
    private:
        CEGUI::Window* nameEditBox;
};
void DynamicEditor::VariableFactory::createNameDisplay(float _top, float _height, CEGUI::Window* _root)//(CEGUI::Window* _rootWindow, TypeTable* _params, const std::string& _factoryName, float* _uiElementTop)
{
    static int uniqueName = 0;
    CEGUI::Window* variableNameDisplay = CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("ComponentSelectionDisplay.layout", _root->getName() + "Show" + uniqueName++);
    variableNameDisplay->setPosition(CEGUI::UVector2({{0.0f, 0.0f}, {0.0f,_top}}));
    variableNameDisplay->setHeight({0.0f, _height});
    variableNameDisplay->setProperty("Text", name);
    _root->addChildWindow(variableNameDisplay);
}
DynamicEditor::DynamicEditor(FreeCamera* camera, EditorMode* _mode)
:editorModes
({
    {{"position","dimensions"}, new DynamicEditor::DerivedModeFactory<BoxDragMode>()},
    {{"points"}, new DynamicEditor::DerivedModeFactory<PointGeometryMode>()},
    {{"position", "radius"}, new DynamicEditor::DerivedModeFactory<CircleDragMode>()},
    {{"position"}, new DynamicEditor::DerivedModeFactory<ClickPlaceMode>()},
}),
editorVariables
({
    {"skin", new ComponentObjectSelectionVariableFactory<Skin>("skin","StaticSkinFactory")},
})
{
    //ctor
    //entityList = new EntityList("Root/EntityList/Listbox");
    camera->activate();
    mCamera = camera;
    instanceTab = getTabControl("Root/Entities");
    typeTab = getTabControl("Root/EntityTypes");
    entityName = CEGUI::System::getSingleton().getGUISheet()->getChildRecursive("Root/Entities/EntityName");
    //nameVariableController = new NameVariableController(entityName, &params);
    nameVariableControllerFactory = new NameVariableControllerFactory("ThisIsAName", entityName);
    assert(entityName);
    instanceTab->getParent()->setEnabled(false);
    typeTab->getParent()->setEnabled(false);
    instanceTab->getParent()->setVisible(false);
    typeTab->getParent()->setVisible(false);

    CEGUI::Window* button = typeTab->getParent()->getChild("Root/EntityTypes/CreateButton");
    button->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::SubscriberSlot(&DynamicEditor::createFactory,this));
    editorMode = _mode;
}

DynamicEditor::~DynamicEditor()
{
    //dtor
    instanceTab->getParent()->destroy();
    typeTab->getParent()->destroy();
    Events::global().unregisterListener(static_cast<EventsListener<FactoryTypeRegisterEvent<Entity>>*>(this), true);
    Events::global().unregisterListener(static_cast<EventsListener<FactoryCreateEvent<Entity>>*>(this), true);
}


EntityList* DynamicEditor::getEntityList()
{
    return editorMode->getEntityList();
}
bool DynamicEditor::createFactory(const CEGUI::EventArgs& _args)
{
    unsigned int index = typeTab->getSelectedTabIndex();
    CEGUI::Window* tab = typeTab->getTabContentsAtIndex(index);
    static_cast<EditorFactoryType*>(tab->getUserData())->createButton(_args);
    return true;
}
bool DynamicEditor::trigger(FactoryCreateEvent<Entity>* event)
{
    std::string name = event->getFactory()->getName();
    if (name != "AIEntityFactory")
    {
        DynamicEditor::EditorFactoryType* factory = editorFactories[name];
        if (factory != nullptr)
        {
            activeEditor = factory->createEditor(instanceTab, event->getFactoryName(), name, this);
        }
    }

    for (unsigned int i = 0; i < deadBodies.size(); i++)
        delete deadBodies[i];
    deadBodies.clear();
    return true;
}

bool DynamicEditor::trigger(FactoryTypeRegisterEvent<Entity>* event)
{
    std::string name = event->getFactoryName();
    if (name != "AIEntityFactory")
    {
        DynamicEditor::EditorFactoryType* factory = searchExistingFactoryInstances(name);
        if (factory != nullptr)
        {
            editorFactories[name] = factory;
        }
    }

    for (unsigned int i = 0; i < deadBodies.size(); i++)
        delete deadBodies[i];
    deadBodies.clear();
    return true;
}
void DynamicEditor::init()
{
    Events::global().registerListener(static_cast<EventsListener<FactoryTypeRegisterEvent<Entity>>*>(this), {eReadQueue|eClearQueue|eBlockQueue});
    Events::global().registerListener(static_cast<EventsListener<FactoryCreateEvent<Entity>>*>(this), {eReadQueue|eClearQueue|eBlockQueue});
}
bool DynamicEditor::activate(const CEGUI::EventArgs& args)
{
    bool ret = InputContext::activate(args);
    instanceTab->getParent()->setEnabled(true);
    typeTab->getParent()->setEnabled(true);
    instanceTab->getParent()->setVisible(true);
    typeTab->getParent()->setVisible(true);
    return ret;
}
void DynamicEditor::deactivate()
{
    instanceTab->getParent()->setEnabled(false);
    typeTab->getParent()->setEnabled(false);
    instanceTab->getParent()->setVisible(false);
    typeTab->getParent()->setVisible(false);
}


DynamicEditor::EditorFactoryType* DynamicEditor::searchExistingFactoryInstances(const std::string& factoryName)
{
    AbstractFactoryBase<Entity>* factory = nullptr; /// FIXME AbstractFactories::global().getFactory<Entity>(factoryName);
    EditorFactoryType* editor = nullptr;
    {
        FactoryParameters parameters(true);
        deadBodies.push_back(factory->use(&parameters));
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
                editor->addInstanceVariableFactory(nameVariableControllerFactory);
                //break;
                goto MATCH_FOUND;
            }
        }
    }
    return nullptr;
MATCH_FOUND:
    TextFileFactoryLoader loader(nullptr, nullptr, true); /// FIXME
    FactoryGetList getList;
    ///Events::global().registerListener<FactoryGetEvent<Entity>>(&getList,{eBlockQueue}); FIXME this is now missing
    //factory->baseInit(factoryName, &loader, &AbstractFactories::global());
    ///Events::global().unregisterListener<FactoryGetEvent<Entity>>(&getList, true);
    std::vector<std::string> values = loader.getUndefinedLog();
    FactoryParameters* params = new FactoryParameters();
    CEGUI::Window* page = CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("EntityTypeTab.layout", factoryName);
    page = page->getChild(factoryName + "Properties");
    float uiElementTop = 0.f;
    for (auto value = values.begin(); value != values.end(); value++)
    {
        auto variable = editorVariables.find(*value);
        if (variable != editorVariables.end())
        {
            editor->addTypeVariable(variable->second->createVariable(page, params->getTypeTable(),factoryName, &uiElementTop));
        }
        else
        {
            TextEditBoxFactory factory(*value, "");
            editor->addTypeVariable(factory.createVariable(page, params->getTypeTable(),factoryName, &uiElementTop));
        }
    }
    page->setProperty("Text",factoryName);
    typeTab->addTab(page);

    page->setUserData(editor);

    CEGUI::Window* factoryNameBox = typeTab->getParent()->getChild("Root/EntityTypes/NewFactoryName");
    editor->setInstanceNameWidget(factoryNameBox);
    return editor;
}

InputContext* DynamicEditor::getActiveEditor()
{
    CEGUI::Window* page = instanceTab->getTabContentsAtIndex(instanceTab->getSelectedTabIndex());
    return static_cast<InputContext*>(page->getUserData());
}
void DynamicEditor::buttonDown(Vec2i mouse, unsigned char button)
{
    getActiveEditor()->buttonDown(mouse,button);
}
void DynamicEditor::mouseMove(Vec2i mouse)
{
    getActiveEditor()->mouseMove(mouse);
}
void DynamicEditor::buttonUp(Vec2i mouse, unsigned char button)
{
    getActiveEditor()->buttonUp(mouse,button);
}
void DynamicEditor::render()
{
    if (instanceTab->getTabCount() != 0)
    {
        InputContext* context = getActiveEditor();
        context->render(); //FIXME put this back in
    }
}

/*bool DynamicEditor::FactoryGetList::trigger(FactoryGetEvent<Entity>* event) /// FIXME put this back in
{
    factories.insert(event->getName());
    return true;
}*/
Level* DynamicEditor::getActiveLevel()
{
    return editorMode->getActiveLevel();
}
bool DynamicEditor::FactoryUseList::trigger(FactoryUsageEvent<b2Body>* event)
{
    factories.push_back(event->get());
    return true;
}



