#ifndef BOXDRAGVARIABLE_H
#define BOXDRAGVARIABLE_H

#include <GameModes/Editor/DynamicEditor/DynamicEditorMode.h>
#include <Input/Mouse/ClickDragEvent.h>

class BoxDragVariable : public DynamicEditorMode
{
    public:
        BoxDragVariable();
        virtual ~BoxDragVariable();
        void buttonDown(Vec2i mouse, unsigned char button);
        void mouseMove(Vec2i mouse);
        void buttonUp(Vec2i mouse, unsigned char button);
        void render();
    protected:
        void finish();
    private:
        bool dragging;
        Vec2i startPos;
        Vec2f topLeft, bottomright;
};

#endif // BOXDRAGVARIABLE_H
