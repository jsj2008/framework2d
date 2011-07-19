#include "BoxDragVariable.h"
#include <AbstractFactory/FactoryParameters.h>

BoxDragVariable::BoxDragVariable(DynamicEditorMode* _editor, FactoryParameters* _params)
:DynamicEditorMode(_editor,_params)
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
        create();
    }
    dragging = false;
}
void BoxDragVariable::finish()
{
    Vec2f pos(topLeft + (bottomright - topLeft)*0.5);
    Vec2f dimensions = bottomright - startPos.ScreenToWorldSpace();
    params->add("position",pos);
    params->add("dimensions",dimensions);
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
