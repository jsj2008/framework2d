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
DynamicEditorMode* DynamicEditor::DerivedModeFactory<mode>::createMode(FactoryParameters* _params)
{
    return new mode(_params);
}

InputContext* DynamicEditor::EditorFactoryType::createEditor(CEGUI::TabControl* _tab, std::string _factoryName, std::string _typeName, DynamicEditor* _editor)
{
    FactoryParameters* params = new FactoryParameters(true);
    DynamicEditorMode* editorMode = modeFactory->createMode(params);

    CEGUI::Window* page = CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("EntityInstanceTab.layout", _factoryName);
    CEGUI::Window* typeNameDisplay = page->getChild(_factoryName + "Tab/EntityTypeName");
    typeNameDisplay->appendText(_typeName);
    page->setProperty("Text",_factoryName);
    _tab->addTab(page);
    page->setUserData(editorMode);

    editorMode->initEditorMode(_factoryName, page, _editor);

    for (auto i = instanceVariableFactories.begin(); i != instanceVariableFactories.end(); i++)
    {
        DynamicEditorVariable* editorVar = (*i)->createVariable(editorMode->getWindow(),params->getTypeTable(), _factoryName);
        editorMode->addVariable(editorVar);
    }

    return editorMode;
}
std::vector<Entity*> deadBodies; /// FIXME
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
    for (unsigned int i = 0; i < deadBodies.size(); i++)
        delete deadBodies[i];
    deadBodies.clear();
    editor->activeEditor = createEditor(editor->instanceTab, name, factoryTypeName, editor);
    editor->instanceTab->setSelectedTabAtIndex(editor->instanceTab->getTabCount()-1);
    std::ofstream file ("Resources/EntityFactories.txt", std::ios::app);
    for (auto i = variables.begin(); i != variables.end(); i++)
    {
        (*i)->addPropertyBagVariable(&loader);
    }
    loader.output(&file);
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
        NameVariableController(CEGUI::Window* _entityName, TypeTable* _params)
        :DynamicEditorVariable(_entityName, _params, "name")
        {
        }
        void finish()
        {
            std::string string = rootWindow->getProperty("Text").c_str();
            if (string != "")
            {
                typeTable->addValue<std::string>(factoryName, string.c_str());
            }
        }
        void addPropertyBagVariable(CppFactoryLoader* _loader)
        {
            std::string string = rootWindow->getProperty("Text").c_str();
            if (string != "")
            {
                _loader->addValue<std::string>(factoryName, string.c_str());
            }
        }
    private:
        //CEGUI::Window* entityName;
};
class NameVariableControllerFactory : public DynamicEditor::VariableFactory
{
    public:
        NameVariableControllerFactory(CEGUI::Window* _nameEditBox){nameEditBox = _nameEditBox;}
        DynamicEditorVariable* createVariable(CEGUI::Window* _rootWindow, TypeTable* _params, const std::string& _factoryName){return new NameVariableController(nameEditBox,_params);}
    private:
        CEGUI::Window* nameEditBox;
};
DynamicEditor::DynamicEditor(FreeCamera* camera, EditorMode* _mode)
:editorModes
({
    {{"position","dimensions"}, new DynamicEditor::DerivedModeFactory<BoxDragMode>()},
    {{"points"}, new DynamicEditor::DerivedModeFactory<PointGeometryMode>()},
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
    nameVariableControllerFactory = new NameVariableControllerFactory(entityName);
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
    AbstractFactoryBase<Entity>* factory = AbstractFactories::global().getFactory<Entity>(factoryName);
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
    TextFileFactoryLoader loader(nullptr, true);
    FactoryGetList getList;
    Events::global().registerListener<FactoryGetEvent>(&getList,{eBlockQueue});
    factory->init(factoryName, &loader, &AbstractFactories::global());
    Events::global().unregisterListener<FactoryGetEvent>(&getList, true);
    std::vector<std::string> values = loader.getUndefinedLog();
    FactoryParameters* params = new FactoryParameters();
    CEGUI::Window *page = CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("EntityTypeTab.layout", factoryName);
    for (auto value = values.begin(); value != values.end(); value++)
    {
        auto variable = editorVariables.find(*value);
        if (variable != editorVariables.end())
        {
            editor->addTypeVariable(variable->second->createVariable(page, params->getTypeTable(),factoryName));
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

bool DynamicEditor::FactoryGetList::trigger(FactoryGetEvent* event)
{
    factories.insert(event->getName());
    return true;
}
bool DynamicEditor::FactoryUseList::trigger(FactoryUsageEvent<b2Body>* event)
{
    factories.push_back(event->get());
    return true;
}

Level* DynamicEditor::getActiveLevel()
{
    return editorMode->getActiveLevel();
}
