#ifndef DYNAMICEDITOR_H
#define DYNAMICEDITOR_H

#include <Input/Mouse/InputContext.h>
#include <GameModes/GameMode.h>
#include <AbstractFactory/FactoryParameters.h>
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
                virtual DynamicEditorMode* createMode()=0;
        };
        template <typename mode>
        class DerivedModeFactory : public ModeFactory
        {
            public:
                DynamicEditorMode* createMode(){return new mode();}
        };

        class VariableFactory
        {
            public:
                virtual DynamicEditorVariable* createVariable()=0;
        };
        template <typename mode>
        class DerivedVariableFactory : public VariableFactory
        {
            public:
                DynamicEditorVariable* createVariable(){return new mode();}
        };
        static std::vector<
            std::pair<
                std::vector<std::string>,
                ModeFactory*>
            > editorModes;
        static std::unordered_map<std::string,VariableFactory*> editorVariables;
};

#endif // DYNAMICEDITOR_H
