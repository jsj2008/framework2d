#include "GeometryEditor.h"
#include <Graphics/GraphicsManager.h>
#include <Level/LevelManager.h>
#include <Input/InputState.h>
#include <Graphics/Camera/FreeCamera.h>
#include <GL/gl.h>

GeometryEditor::GeometryEditor(FreeCamera* camera, const Rect& _Rect)
:ClickReleaseEvent(_Rect)
{
    //ctor
    mInputState = new InputState;
    camera->registerWithInputState(mInputState);
    mCamera = camera;
    Rect fullScreen(0,0,10000,10000);
    mInputState->registerEvent(this);
}

GeometryEditor::~GeometryEditor()
{
    //dtor
}
void GeometryEditor::click(Vec2i mouse, unsigned char button)
{
    if (button == 1 && def.numVertices < b2_maxPolygonVertices)
    {
        Vec2f point = mouse.ScreenToWorldSpace();
        def.addPoint(point);
    }
    if (def.numVertices == b2_maxPolygonVertices || button == 3)
    {
        if (def.numVertices > 2)
        {
            if (def.sort())
                g_LevelManager.addPlatform(&def);
        }
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
