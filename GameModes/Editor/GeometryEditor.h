#ifndef GEOMETRYEDITOR_H
#define GEOMETRYEDITOR_H

#include <Input/Mouse/ClickReleaseEvent.h>
#include <Factory/ConvexGeometryDef.h>
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
        ConvexGeometryDef def;
        CEGUI::Window* materialName;
};

#endif // GEOMETRYEDITOR_H
