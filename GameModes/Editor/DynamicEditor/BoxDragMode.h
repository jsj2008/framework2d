#ifndef BOXDRAGVMODE_H
#define BOXDRAGVMODE_H

#include <GameModes/Editor/DynamicEditor/DynamicEditorMode.h>
#include <Input/Mouse/ClickDragEvent.h>

class BoxDragMode: public DynamicEditorMode
{
    public:
        BoxDragMode(CEGUI::Window* _window, FactoryParameters* _params);
        virtual ~BoxDragMode();
        void buttonDown(Vec2i mouse, unsigned char button);
        void mouseMove(Vec2i mouse);
        void buttonUp(Vec2i mouse, unsigned char button);
        void render();
        void finish();
    protected:
    private:
        bool dragging;
        Vec2i startPos;
        Vec2f topLeft, bottomright;
};

#endif // BOXDRAGVMODE_H
