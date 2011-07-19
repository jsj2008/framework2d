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
        DynamicEditorMode* createEditorMode(const std::string& factoryName);
        InputContext* activeEditor;
        FactoryParameters params;
        class ModeFactory
        {
            public:
                virtual DynamicEditorMode* createMode(DynamicEditorMode* _editor, FactoryParameters* _params)=0;
        };
        template <typename mode>
        class DerivedModeFactory : public ModeFactory
        {
            public:
                DynamicEditorMode* createMode(DynamicEditorMode* _editor, FactoryParameters* _params){return new mode(_editor, _params);}
        };

        class VariableFactory
        {
            public:
                virtual DynamicEditorVariable* createVariable(DynamicEditorMode* _editor, FactoryParameters* _params)=0;
        };
        template <typename mode>
        class DerivedVariableFactory : public VariableFactory
        {
            public:
                DynamicEditorVariable* createVariable(DynamicEditorMode* _editor, FactoryParameters* _params){return new mode(_editor,_params);}
        };
        static std::vector<
            std::pair<
                std::vector<std::string>,
                ModeFactory*>
            > editorModes;
        static std::unordered_map<std::string,VariableFactory*> editorVariables;

        class FactoryGetList: public EventsListener<FactoryGetEvent>
        {
            public:
                std::unordered_set<std::string>& getFactories(){return factories;}
            protected:
                bool trigger(FactoryGetEvent* event);
                std::unordered_set<std::string> factories;
        };
        CEGUI::Window* window;
};

#endif // DYNAMICEDITOR_H
