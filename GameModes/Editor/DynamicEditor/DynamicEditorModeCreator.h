#ifndef DYNAMICEDITORMODECREATOR_H
#define DYNAMICEDITORMODECREATOR_H

#include <vector>
#include <string>
class DynamicEditor;
class FactoryParameters;
class DynamicEditorMode;

class DynamicEditorModeCreator
{
    public:
        DynamicEditorModeCreator(std::vector<std::string>* _variableNames);
        virtual ~DynamicEditorModeCreator();
        DynamicEditorMode* createEditorModes(DynamicEditor* editor, FactoryParameters* params);
    protected:
    private:
        std::vector<std::string>* variableNames;
};

#endif // DYNAMICEDITORMODECREATOR_H
