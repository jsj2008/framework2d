#ifndef TEXTEDITBOX_H
#define TEXTEDITBOX_H

#include <CEGUI/CEGUI.h>
#include <GameModes/Editor/DynamicEditor.h>
#include <GameModes/Editor/DynamicEditor/DynamicEditorVariable.h>

class TextEditBox : public DynamicEditorVariable
{
    public:
        TextEditBox(CEGUI::Window* _rootWindow, TypeTable* _params, const std::string& _name,
            const std::string& _defaultValue, const std::string& _factoryName, float* _uiElementHeight);
        virtual ~TextEditBox();
        void addPropertyBagVariable(CppFactoryLoader* _loader);
    protected:
        void finish();
    private:
        std::string defaultValue;
};

class TextEditBoxFactory : public DynamicEditor::VariableFactory /// Should move this into another file, to prevent the source of this including DynamicEditor
{
    public:
        TextEditBoxFactory(const std::string& _name, const std::string& _defaultValue):VariableFactory(_name){;defaultValue = _defaultValue;}
        DynamicEditorVariable* createVariable(CEGUI::Window* _rootWindow, TypeTable* _params, const std::string& _factoryName, float* _uiElementHeight);
    private:
        std::string defaultValue;
};
#endif // TEXTEDITBOX_H
