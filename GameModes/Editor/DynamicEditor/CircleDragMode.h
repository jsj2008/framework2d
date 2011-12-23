#ifndef CIRCLEDRAGMODE_H
#define CIRCLEDRAGMODE_H

#include <GameModes/Editor/DynamicEditor/DynamicEditorMode.h>

class CircleDragMode : public DynamicEditorMode
{
    public:
        CircleDragMode(CEGUI::Window* _window, FactoryParameters* _params);
        virtual ~CircleDragMode();
        void buttonDown(Vec2i mouse, unsigned char button);
        void mouseMove(Vec2i mouse);
        void buttonUp(Vec2i mouse, unsigned char button);
        void render();
        void finish();
    protected:
    private:
        bool dragging;
        Vec2f center;
        float radius;
};

#endif // CIRCLEDRAGMODE_H
