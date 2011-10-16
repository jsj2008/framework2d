#include "CircleDragMode.h"
#include <Types/TypeTable.h>

CircleDragMode::CircleDragMode(CEGUI::Window* _window, FactoryParameters* _params)
:DynamicEditorMode(_window, _params)
{
    //ctor
}

CircleDragMode::~CircleDragMode()
{
    //dtor
}

void CircleDragMode::buttonDown(Vec2i mouse, unsigned char button)
{
    center = mouse.ScreenToWorldSpace();
    radius = 0.0f;
    dragging = true;
}
void CircleDragMode::mouseMove(Vec2i mouse)
{
    Vec2f edge = mouse.ScreenToWorldSpace();
    radius = (edge - center).Length();
}
void CircleDragMode::buttonUp(Vec2i mouse, unsigned char button)
{
    Vec2f edge = mouse.ScreenToWorldSpace();
    radius = (edge - center).Length();
    if (radius > 1.0f)
    {
        create();
    }
    dragging = false;
}
void CircleDragMode::finish()
{
    typeTable->addValue("position",center);
    typeTable->addValue("radius",radius);
}
#include <GL/gl.h>
const float DEG2RAD = 3.14159/180;
void CircleDragMode::render()
{
    if (dragging)
    {
        glBegin(GL_LINE_LOOP);

        for (int i=0; i != 360; i++)
        {
            float degInRad = i*DEG2RAD;
            glVertex2f(center.x + cos(degInRad)*radius, center.y + sin(degInRad)*radius);
        }

        glEnd();
        /*glBegin(GL_LINE_LOOP);
        glVertex2f(topLeft.x,topLeft.y);
        glVertex2f(topLeft.x,bottomright.y);
        glVertex2f(bottomright.x,bottomright.y);
        glVertex2f(bottomright.x,topLeft.y);
        glEnd();*/
    }
}
