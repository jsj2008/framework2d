#ifndef TEXTEDITBOX_H
#define TEXTEDITBOX_H

#include <CEGUI/CEGUI.h>
#include <GameModes/Editor/DynamicEditor/DynamicEditorVariable.h>

class TextEditBox : public DynamicEditorVariable
{
    public:
        TextEditBox(CEGUI::Window* _rootWindow, TypeTable* _params, const std::string& _name, const std::string& _defaultValue, const std::string& _factoryName);
        virtual ~TextEditBox();
        void addPropertyBagVariable(CppFactoryLoader* _loader);
    protected:
        void finish();
    private:
        CEGUI::Window* widget;
        std::string name, defaultValue;
};

#endif // TEXTEDITBOX_H
