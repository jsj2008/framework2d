#include "BoxDragMode.h"
#include <AbstractFactory/FactoryParameters.h>

BoxDragMode::BoxDragMode(FactoryParameters* _params)
:DynamicEditorMode(_params)
{
    //ctor
}

BoxDragMode::~BoxDragMode()
{
    //dtor
}

void BoxDragMode::buttonDown(Vec2i mouse, unsigned char button)
{
    startPos = mouse;
    topLeft = mouse.ScreenToWorldSpace();
    bottomright = topLeft;
    dragging = true;
}
void BoxDragMode::mouseMove(Vec2i mouse)
{
    bottomright = mouse.ScreenToWorldSpace();
}
void BoxDragMode::buttonUp(Vec2i mouse, unsigned char button)
{
    bottomright = mouse.ScreenToWorldSpace();
    Vec2f dimensions = bottomright - startPos.ScreenToWorldSpace();
    if (dimensions.x > 1.0f && dimensions.y > 1.0f)
    {
        create();
    }
    dragging = false;
}
void BoxDragMode::finish()
{
    Vec2f pos(topLeft + (bottomright - topLeft)*0.5);
    Vec2f dimensions = bottomright - startPos.ScreenToWorldSpace();
    typeTable->addValue("position",pos);
    typeTable->addValue("dimensions",dimensions);
}
#include <GL/gl.h>
void BoxDragMode::render()
{
    if (dragging)
    {
        glBegin(GL_LINE_LOOP);
        glVertex2f(topLeft.x,topLeft.y);
        glVertex2f(topLeft.x,bottomright.y);
        glVertex2f(bottomright.x,bottomright.y);
        glVertex2f(bottomright.x,topLeft.y);
        glEnd();
    }
}
