#ifndef DYNAMICEDITORMODE_H
#define DYNAMICEDITORMODE_H

#include <Input/Mouse/InputContext.h>
#include <GameModes/Editor/DynamicEditor/DynamicEditorVariable.h>

class DynamicEditorMode : public InputContext, public DynamicEditorVariable
{
    public:
        DynamicEditorMode();
        virtual ~DynamicEditorMode();
        void initEditorMode(std::string _name){name = _name;}
        /// Called during initialisation also
        void addVariable(DynamicEditorVariable* _variable){variables.push_back(_variable);}
    protected:
        void create();
    private:
        std::vector<DynamicEditorVariable*> variables;
        std::string name;
};

#endif // DYNAMICEDITORMODE_H
