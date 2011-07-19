#ifndef TEXTEDITBOX_H
#define TEXTEDITBOX_H

#include <CEGUI/CEGUI.h>
#include <GameModes/Editor/DynamicEditor/DynamicEditorVariable.h>

class GameConsoleStringSetCommand;

class TextEditBox : public DynamicEditorVariable
{
    public:
        TextEditBox(DynamicEditorMode* _editor, FactoryParameters* _params);
        virtual ~TextEditBox();
    protected:
        void finish();
    private:
        GameConsoleStringSetCommand* command;
        CEGUI::Window* widget;
};

#endif // TEXTEDITBOX_H
