#include "BoxDragVariable.h"
#include <AbstractFactory/FactoryParameters.h>

BoxDragVariable::BoxDragVariable()
{
    //ctor
}

BoxDragVariable::~BoxDragVariable()
{
    //dtor
}

void BoxDragVariable::buttonDown(Vec2i mouse, unsigned char button)
{
    startPos = mouse;
    topLeft = mouse.ScreenToWorldSpace();
    bottomright = topLeft;
    dragging = true;
}
void BoxDragVariable::mouseMove(Vec2i mouse)
{
    bottomright = mouse.ScreenToWorldSpace();
}
void BoxDragVariable::buttonUp(Vec2i mouse, unsigned char button)
{
    bottomright = mouse.ScreenToWorldSpace();
    Vec2f dimensions = bottomright - startPos.ScreenToWorldSpace();
    if (dimensions.x > 1.0f && dimensions.y > 1.0f)
    {
        Vec2f pos(topLeft + (bottomright - topLeft)*0.5);
        params->add("position",pos);
        params->add("dimensions",dimensions);
        finish();
    }
    dragging = false;
}
#include <GL/gl.h>
void BoxDragVariable::render()
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
