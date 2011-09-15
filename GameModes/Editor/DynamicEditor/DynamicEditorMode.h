#ifndef DYNAMICEDITORMODE_H
#define DYNAMICEDITORMODE_H

#include <Input/Mouse/InputContext.h>
#include <GameModes/Editor/DynamicEditor/DynamicEditorVariable.h>
class FactoryParameters;
class DynamicEditor;

class DynamicEditorMode : public InputContext, public DynamicEditorVariable
{
    public:
        DynamicEditorMode(FactoryParameters* _params);
        virtual ~DynamicEditorMode();
        void initEditorMode(std::string _name, CEGUI::Window* _window, DynamicEditor* _editor);
        /// Called during initialisation also
        void addVariable(DynamicEditorVariable* _variable){variables.push_back(_variable);}
        CEGUI::Window* getWindow(){return rootWindow;}
        void addPropertyBagVariable(CppFactoryLoader* _loader);
        bool destroySelf(const CEGUI::EventArgs&);
    protected:
        void create();
    private:
        DynamicEditor* editor;
        FactoryParameters* params;
        std::vector<DynamicEditorVariable*> variables;
        std::string name;
};

#endif // DYNAMICEDITORMODE_H
