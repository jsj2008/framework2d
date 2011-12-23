#ifndef DYNAMICEDITORVARIABLE_H
#define DYNAMICEDITORVARIABLE_H

#include <CEGUI/CEGUI.h>
#include <string>
class TypeTable;
class CppFactoryLoader;

class DynamicEditorVariable
{
    public:
        DynamicEditorVariable(TypeTable* _params, const std::string& _name);
        virtual ~DynamicEditorVariable();
        virtual void finish()=0;
        virtual void addPropertyBagVariable(CppFactoryLoader* _loader)=0;
        CEGUI::Window* getWidget(){return widget;}
    protected:
        CEGUI::Window* widget;
        TypeTable* typeTable;
        std::string name;
    private:
};

#endif // DYNAMICEDITORVARIABLE_H
