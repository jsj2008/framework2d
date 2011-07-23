#ifndef DYNAMICEDITORMODE_H
#define DYNAMICEDITORMODE_H

#include <Input/Mouse/InputContext.h>
#include <GameModes/Editor/DynamicEditor/DynamicEditorVariable.h>
class FactoryParameters;

class DynamicEditorMode : public InputContext, public DynamicEditorVariable
{
    public:
        DynamicEditorMode(FactoryParameters* _params);
        virtual ~DynamicEditorMode();
        void initEditorMode(std::string _name, CEGUI::Window* _window);
        /// Called during initialisation also
        void addVariable(DynamicEditorVariable* _variable){variables.push_back(_variable);}
        CEGUI::Window* getWindow(){return rootWindow;}
        void addPropertyBagVariable(CppFactoryLoader* _loader);
    protected:
        void create();
    private:
        FactoryParameters* params;
        std::vector<DynamicEditorVariable*> variables;
        std::string name;
};

#endif // DYNAMICEDITORMODE_H
