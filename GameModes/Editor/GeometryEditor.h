#ifndef GEOMETRYEDITOR_H
#define GEOMETRYEDITOR_H

#include <Input/Mouse/ClickReleaseEvent.h>
#include <Entities/EntityFactory.h>
#include <Factory/ConvexGeometryDef.h>

class GeometryEditor : public ClickReleaseEvent
{
    public:
        GeometryEditor(const Rect& _Rect);
        virtual ~GeometryEditor();
        void click(Vec2i mouse, unsigned char button);
        void render();
    protected:
    private:
        ConvexGeometryDef def;
};

#endif // GEOMETRYEDITOR_H
