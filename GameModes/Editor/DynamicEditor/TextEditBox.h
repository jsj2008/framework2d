#ifndef TEXTEDITBOX_H
#define TEXTEDITBOX_H

#include <CEGUI/CEGUI.h>
#include <GameModes/Editor/DynamicEditor/DynamicEditorVariable.h>

class TextEditBox : public DynamicEditorVariable
{
    public:
        TextEditBox(CEGUI::Window* _rootWindow, TypeTable* _params);
        virtual ~TextEditBox();
        void addPropertyBagVariable(CppFactoryLoader* _loader);
    protected:
        void finish();
    private:
        CEGUI::Window* widget;
};

#endif // TEXTEDITBOX_H
