#ifndef GEOMETRYEDITOR_H
#define GEOMETRYEDITOR_H

#include <Input/Mouse/ClickReleaseEvent.h>
#include <GameModes/GameMode.h>
class FreeCamera;
namespace CEGUI
{
    class Window;
}

class GeometryEditor : public GameMode, public ClickReleaseEvent
{
    public:
        GeometryEditor(FreeCamera* camera);
        virtual ~GeometryEditor();
        void init();
        void click(Vec2i mouse, unsigned char button);
        void render();
    protected:
    private:
        std::vector<Vec2f> points;
        CEGUI::Window* materialName;
        bool sort();
};

#endif // GEOMETRYEDITOR_H
