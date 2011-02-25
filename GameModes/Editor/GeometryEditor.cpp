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
void GeometryEditor::click(Vec2i mouse, unsigned char button)
{
    if (button == 1)
    {
        Vec2f point = mouse.ScreenToWorldSpace();
        def.addPoint(point);
    }
    if (def.numVertices == b2_maxPolygonVertices || button == 3)
    {
        if (def.sort())
            g_LevelManager.addPlatform(&def);
        def.numVertices = 0;
    }
}

void GeometryEditor::render()
{
    if (def.numVertices > 0)
    {
        glBegin(GL_POINTS);
        glVertex2f(def.vertices[0].x,def.vertices[0].y);
        glEnd();
        glBegin(GL_LINE_STRIP);
        for (unsigned char i = 0; i < def.numVertices; i++)
        {
            glVertex2f(def.vertices[i].x,def.vertices[i].y);
        }
        glEnd();
    }
}
