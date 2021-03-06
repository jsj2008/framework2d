#ifndef DYNAMICEDITOR_H
#define DYNAMICEDITOR_H

#include <unordered_set>
#include <Input/Mouse/InputContext.h>
#include <GameModes/GameMode.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Events/EventListener.h>
#include <Events/Events/FactoryGetEvent.h>
#include <Events/Events/FactoryUsageEvent.h>
#include <AbstractFactory/AbstractFactoryList.h>
#include <Events/Events/FactoryCreateEvent.h>
#include <Box2D/Box2D.h>
class Entity;
class FreeCamera;
class DynamicEditorMode;
class DynamicEditorVariable;
class EditorMode;
class Level;
class EntityList;

class DynamicEditor : public GameMode, public InputContext, public EventsListener<FactoryCreateEvent<Entity>>, public EventsListener<FactoryTypeRegisterEvent<Entity>>
{
    public:
        DynamicEditor(FreeCamera* camera, EditorMode* _mode);
        virtual ~DynamicEditor();
        void init();
        void buttonDown(Vec2i mouse, unsigned char button);
        void mouseMove(Vec2i mouse);
        void buttonUp(Vec2i mouse, unsigned char button);
        bool trigger(FactoryCreateEvent<Entity>* event);
        bool trigger(FactoryTypeRegisterEvent<Entity>* event);
        void render();
        bool activate(const CEGUI::EventArgs&);
        void deactivate();
        EntityList* getEntityList();

        Level* getActiveLevel();

        class VariableFactory;
    protected:
    private:
        class EditorFactory;
        class EditorFactoryType;
        class ModeFactory;
        DynamicEditorMode* createEditorMode(const std::string& factoryName);
        EditorFactoryType* searchExistingFactoryInstances(const std::string& factoryName);
        bool createFactory(const CEGUI::EventArgs& _args);
        InputContext* activeEditor;
        std::unordered_map<std::string, EditorFactoryType*> editorFactories;
        FactoryParameters params;
        InputContext* getActiveEditor();

        class EditorFactoryType
        {
            public:
                EditorFactoryType(ModeFactory* _modeFactory, DynamicEditor* _editor, const std::string& _factoryTypeName){modeFactory = _modeFactory;editor = _editor;factoryTypeName = _factoryTypeName;}
                ~EditorFactoryType();
                EditorFactory* createFactory(CEGUI::TabControl* _tab, std::string _factoryName);
                void addTypeVariable(DynamicEditorVariable* _variable){variables.push_back(_variable);}
                void addInstanceVariableFactory(VariableFactory* _variableFactory){instanceVariableFactories.push_back(_variableFactory);}
                bool createButton(const CEGUI::EventArgs&);
                void setInstanceNameWidget(CEGUI::Window* _instanceNameWidget){instanceNameWidget = _instanceNameWidget;}
                const std::string& getName(){return factoryTypeName;}
                InputContext* createEditor(CEGUI::TabControl* _tab, std::string _factoryName, std::string _typeName, DynamicEditor* _editor);
            private:
                std::string factoryTypeName;
                CEGUI::Window* instanceNameWidget;
                friend class EditorFactory;
                DynamicEditor* editor;
                ModeFactory* modeFactory;
                std::vector<DynamicEditorVariable*> variables;
                std::vector<VariableFactory*> instanceVariableFactories;
        };

        class ModeFactory
        {
            public:
                virtual DynamicEditorMode* createMode(CEGUI::Window* _window, FactoryParameters* _params)=0;
        };
        template <typename mode>
        class DerivedModeFactory : public ModeFactory
        {
            public:
                DynamicEditorMode* createMode(CEGUI::Window* _window, FactoryParameters* _params);
        };
    public: /// FIXME
        class VariableFactory /// Have a little icon for what goes next to it
        {
            public:
                VariableFactory(const std::string& _name){name = _name;}
                virtual DynamicEditorVariable* createVariable(CEGUI::Window* _rootWindow, TypeTable* _params, const std::string& _factoryName, float* _uiElementTop)=0;
                const std::string& getName(){return name;}
            protected:
                void createNameDisplay(float _top, float _height, CEGUI::Window* _root);
                std::string name;
        };
    private:
        template <typename mode>
        class DerivedVariableFactory : public VariableFactory
        {
            public:
                DynamicEditorVariable* createVariable(CEGUI::Window* _rootWindow, TypeTable* _params, const std::string& _factoryName, float* _uiElementTop){return new mode(_rootWindow,_params, _factoryName, _uiElementTop);}
        };
        std::vector<
            std::pair<
                std::vector<std::string>,
                ModeFactory*>
            > editorModes;
        std::unordered_map<std::string,VariableFactory*> editorVariables;
        //DynamicEditorVariable* nameVariableController;
        VariableFactory* nameVariableControllerFactory;

        class FactoryGetList //: public EventsListener<FactoryGetEvent<Entity>> /// FIXME this is now missing
        {
            public:
                std::unordered_set<std::string>& getFactories(){return factories;}
            protected:
                //bool trigger(FactoryGetEvent<Entity>* event);
                std::unordered_set<std::string> factories;
        };
        class FactoryUseList: public EventsListener<FactoryUsageEvent<b2Body>>
        {
            public:
                std::vector<b2Body*>& getBodies(){return factories;}
            protected:
                bool trigger(FactoryUsageEvent<b2Body>* event);
                std::vector<b2Body*> factories;
        };
        CEGUI::TabControl* instanceTab;
        CEGUI::TabControl* typeTab;
        CEGUI::Window* entityName;
        EditorMode* editorMode;
        bool v_Update(){return true;}  // FIXME
};

#endif // DYNAMICEDITOR_H
