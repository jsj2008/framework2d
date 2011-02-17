#include "GeometryEditor.h"
#include <Graphics/GraphicsManager.h>

GeometryEditor::GeometryEditor(const Rect& _Rect)
:ClickReleaseEvent(_Rect)
{
    //ctor
}

GeometryEditor::~GeometryEditor()
{
    //dtor
}
extern Entity* g_Temp;
void GeometryEditor::click(int mouseX, int mouseY)
{
    float x = mouseX + g_GraphicsManager.getViewX();
    float y = mouseY + g_GraphicsManager.getViewY();
    b2Vec2 point(x/PIXELS_PER_METER,y/PIXELS_PER_METER);
    def.addPoint(point);
    if (def.numPoints == 4)
    {
        unsigned int platform = g_EntityFactory.addEntityDef(def);
        b2Vec2 origin(0,0);
        g_Temp = g_EntityFactory.createEntity(platform,origin);
        def.numPoints = 0;
    }
}
