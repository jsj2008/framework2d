#ifndef DYNAMICEDITORMODE_H
#define DYNAMICEDITORMODE_H

#include <Input/Mouse/InputContext.h>
#include <GameModes/Editor/DynamicEditor/DynamicEditorVariable.h>

class DynamicEditorMode : public InputContext, public DynamicEditorVariable
{
    public:
        DynamicEditorMode(DynamicEditorMode* _editor, FactoryParameters* _params);
        virtual ~DynamicEditorMode();
        void initEditorMode(std::string _name, CEGUI::Window* _window);
        /// Called during initialisation also
        void addVariable(DynamicEditorVariable* _variable){variables.push_back(_variable);}
        void addChildWindow(CEGUI::Window* _window);
    protected:
        void create();
    private:
        std::vector<DynamicEditorVariable*> variables;
        std::string name;
        CEGUI::Window* window;
};

#endif // DYNAMICEDITORMODE_H
