#ifndef DYNAMICEDITORVARIABLE_H
#define DYNAMICEDITORVARIABLE_H

#include <string>
class DynamicEditor;
class FactoryParameters;

class DynamicEditorVariable
{
    public:
        DynamicEditorVariable();
        void initEditorVariable(DynamicEditor* _editor, FactoryParameters* _params);
        virtual ~DynamicEditorVariable();
    protected:
        DynamicEditor* editor;
        FactoryParameters* params;
    private:
};

#endif // DYNAMICEDITORVARIABLE_H
