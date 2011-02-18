#ifndef GEOMETRYEDITOR_H
#define GEOMETRYEDITOR_H

#include <Input/Mouse/ClickReleaseEvent.h>
#include <Entities/EntityFactory.h>


class GeometryEditor : public ClickReleaseEvent
{
    public:
        GeometryEditor(const Rect& _Rect);
        virtual ~GeometryEditor();
        void click(int mouseX, int mouseY, unsigned char button);
        void render();
    protected:
    private:
        PlatformDef def;
};

#endif // GEOMETRYEDITOR_H
