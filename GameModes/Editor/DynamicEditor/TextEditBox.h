#ifndef TEXTEDITBOX_H
#define TEXTEDITBOX_H

#include <GameModes/Editor/DynamicEditor/DynamicEditorVariable.h>


class TextEditBox : public DynamicEditorVariable
{
    public:
        TextEditBox();
        virtual ~TextEditBox();
    protected:
        void finish();
    private:
};

#endif // TEXTEDITBOX_H
