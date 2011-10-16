#ifndef POINTGEOMETRYMODE_H
#define POINTGEOMETRYMODE_H

#include <GameModes/Editor/DynamicEditor/DynamicEditorMode.h>


class PointGeometryMode : public DynamicEditorMode
{
    public:
        PointGeometryMode(CEGUI::Window* _window, FactoryParameters* _params);
        virtual ~PointGeometryMode();
        void buttonDown(Vec2i mouse, unsigned char button);
        void mouseMove(Vec2i mouse);
        void buttonUp(Vec2i mouse, unsigned char button);
        void render();
    protected:
        void finish();
    private:
        bool sort();
        Vec2i position;
        Vec2f worldPosition;
        std::vector<Vec2f> points;
};

#endif // POINTGEOMETRYMODE_H
