#include "SelectionBox.h"
#include <GL/gl.h>

SelectionBox::SelectionBox(const Rect& _Rect, int _numElements)
:ClickReleaseEvent(_Rect)
{
    //ctor
    numElements = _numElements;
    div = (mRect.x2 - mRect.x)/numElements;
}

SelectionBox::~SelectionBox()
{
    //dtor
}
/// This only works horizontally atm
void SelectionBox::click(Vec2i mouse, unsigned char button)
{
    mouse.x -= mRect.x;
    int newSelection = mouse.x / div;
    currentSelection = newSelection;
    selectionTrigger();
}

void SelectionBox::render()
{
    glPushMatrix(); /// Setting states
    glLoadIdentity();
    glColor3f(0,0,0);

    glBegin(GL_LINES);
    glVertex2i(mRect.x,mRect.y);
    glVertex2i(mRect.x2,mRect.y);

    glVertex2i(mRect.x2,mRect.y);
    glVertex2i(mRect.x2,mRect.y2);

    glVertex2i(mRect.x2,mRect.y2);
    glVertex2i(mRect.x,mRect.y2);

    glVertex2i(mRect.x,mRect.y2);
    glVertex2i(mRect.x,mRect.y);

    for (int i = 0; i < numElements; i++)
    {
        glVertex2i(mRect.x+(i*div),mRect.y);
        glVertex2i(mRect.x+(i*div),mRect.y2);
    }
    glEnd();

    glPopMatrix(); /// Reverting defaults
    glColor3f(1,1,1);
}
