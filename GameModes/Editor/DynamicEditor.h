#ifndef DYNAMICEDITOR_H
#define DYNAMICEDITOR_H

#include <unordered_set>
#include <Input/Mouse/InputContext.h>
#include <GameModes/GameMode.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Events/EventListener.h>
#include <Events/Events/FactoryGetEvent.h>
class Entity;
class FreeCamera;
class DynamicEditorMode;
class DynamicEditorVariable;

class DynamicEditor : public GameMode, public InputContext
{
    public:
        DynamicEditor(FreeCamera* camera);
        virtual ~DynamicEditor();
        void init();
        void buttonDown(Vec2i mouse, unsigned char button);
        void mouseMove(Vec2i mouse);
        void buttonUp(Vec2i mouse, unsigned char button);

    protected:
    private:
        class EditorFactory;
        class EditorFactoryType;
        class ModeFactory;
        class VariableFactory;
        DynamicEditorMode* createEditorMode(const std::string& factoryName);
        EditorFactory* searchExistingFactoryInstances(const std::string& factoryName, bool _createType);
        //EditorFactoryType* createEditorFactoryType(const std::string& factoryName);
        InputContext* activeEditor;
        std::vector<InputContext*> factoryInstances;
        std::vector<EditorFactoryType*> factoryTypes;
        std::unordered_map<std::string, EditorFactory*> editorFactories;
        FactoryParameters params;

        class EditorFactory
        {
            public:
                EditorFactory(EditorFactoryType* _factoryType){factoryType = _factoryType;}
                ~EditorFactory();
                InputContext* createEditor(CEGUI::TabControl* _tab, std::string _factoryName);
            private:
                EditorFactoryType* factoryType;
        };
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
                virtual DynamicEditorMode* createMode(FactoryParameters* _params)=0;
        };
        template <typename mode>
        class DerivedModeFactory : public ModeFactory
        {
            public:
                DynamicEditorMode* createMode(FactoryParameters* _params);
        };

        class VariableFactory
        {
            public:
                virtual DynamicEditorVariable* createVariable(CEGUI::Window* _rootWindow, TypeTable* _params)=0;
        };
        template <typename mode>
        class DerivedVariableFactory : public VariableFactory
        {
            public:
                DynamicEditorVariable* createVariable(CEGUI::Window* _rootWindow, TypeTable* _params){return new mode(_rootWindow,_params);}
        };
        std::vector<
            std::pair<
                std::vector<std::string>,
                ModeFactory*>
            > editorModes;
        std::unordered_map<std::string,VariableFactory*> editorVariables;

        class FactoryGetList: public EventsListener<FactoryGetEvent>
        {
            public:
                std::unordered_set<std::string>& getFactories(){return factories;}
            protected:
                bool trigger(FactoryGetEvent* event);
                std::unordered_set<std::string> factories;
        };
        CEGUI::TabControl* instanceTab;
        CEGUI::TabControl* typeTab;
};

#endif // DYNAMICEDITOR_H
