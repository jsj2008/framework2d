#include "GeometryEditor.h"
#include <Graphics/GraphicsManager.h>
#include <Level/LevelManager.h>
#include <Graphics/Camera/FreeCamera.h>
#include <CEGUI/CEGUI.h>
#include <GL/gl.h>

GeometryEditor::GeometryEditor(FreeCamera* camera)
{
    //ctor
    def.numVertices = 0;
    camera->activate();
    mCamera = camera;
    //g_InputManager.registerStateSelect(this,"GeometryEditor");
    materialName = NULL;
}


void GeometryEditor::init()
{
    materialName = CEGUI::System::getSingleton().getGUISheet()->getChildRecursive("GeometryEditor/Textbox");
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
            {
                CEGUI::String str = materialName->getText();
                if (str.size() != 0)
                {
                    def.setMaterial(str.c_str());
                }
                else
                {
                    def.setMaterial("");
                }
                g_LevelManager.addBody(def);
            }
        }
        def.numVertices = 0;
    }
}

void GeometryEditor::render()
{
    if (def.numVertices > 0)
    {
        glBegin(GL_POINTS);
        glVertex2f(def.getVertex(0).x,def.getVertex(0).y);
        glEnd();
        glBegin(GL_LINE_STRIP);
        for (unsigned char i = 0; i < def.numVertices; i++)
        {
            glVertex2f(def.getVertex(i).x,def.getVertex(i).y);
        }
        glEnd();
    }
}
