#include "GeometryEditor.h"
#include <Graphics/GraphicsManager.h>
#include <Level/LevelManager.h>
#include <GL/gl.h>

GeometryEditor::GeometryEditor(const Rect& _Rect)
:ClickReleaseEvent(_Rect)
{
    //ctor
}

GeometryEditor::~GeometryEditor()
{
    //dtor
}
void GeometryEditor::click(int mouseX, int mouseY, unsigned char button)
{
    if (button == 1)
    {
        float x = mouseX + g_GraphicsManager.getViewX();
        float y = mouseY + g_GraphicsManager.getViewY();
        b2Vec2 point(x/g_GraphicsManager.getPixelsPerMeter(),y/g_GraphicsManager.getPixelsPerMeter());
        def.addPoint(point);
    }
    if (def.numPoints == b2_maxPolygonVertices || button == 3)
    {
        if (def.sort())
            g_LevelManager.addPlatform(&def);
        def.numPoints = 0;
    }
}

void GeometryEditor::render()
{
    if (def.numPoints > 0)
    {
        glBegin(GL_POINTS);
        glVertex2f(def.points[0].x,def.points[0].y);
        glEnd();
        glBegin(GL_LINE_STRIP);
        for (unsigned char i = 0; i < def.numPoints; i++)
        {
            glVertex2f(def.points[i].x,def.points[i].y);
        }
        glEnd();
    }
}
