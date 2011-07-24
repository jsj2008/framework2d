#ifndef DYNAMICEDITORVARIABLE_H
#define DYNAMICEDITORVARIABLE_H

#include <CEGUI/CEGUI.h>
#include <string>
class TypeTable;
class CppFactoryLoader;

class DynamicEditorVariable
{
    public:
        DynamicEditorVariable(CEGUI::Window* _rootWindow, TypeTable* _params, const std::string& _factoryName);
        virtual ~DynamicEditorVariable();
        virtual void finish()=0;
        virtual void addPropertyBagVariable(CppFactoryLoader* _loader)=0;
    protected:
        CEGUI::Window* rootWindow;
        TypeTable* typeTable;
        std::string factoryName;
    private:
};

#endif // DYNAMICEDITORVARIABLE_H
