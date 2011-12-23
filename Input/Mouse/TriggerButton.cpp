#include "TriggerButton.h"
#include <Input/Mouse/TriggerListener.h>

TriggerButton::TriggerButton(const Rect _rect, TriggerListener* _listener)
:ClickReleaseEvent(_rect)
{
    //ctor
    listener = _listener;
}

TriggerButton::~TriggerButton()
{
    //dtor
}

void TriggerButton::click(Vec2i mouse, unsigned char button)
{
    listener->trigger(this, button);
}
#include <GL/gl.h>
void TriggerButton::render()
{
    glPushMatrix();
    glLoadIdentity();
    glColor3f(0,0,1);
    glBegin(GL_QUADS);
    glVertex2i(mRect.x,mRect.y);
    glVertex2i(mRect.x,mRect.y2);
    glVertex2i(mRect.x2,mRect.y2);
    glVertex2i(mRect.x2,mRect.y);
    glEnd();
    glColor3f(1,1,1);
    glPopMatrix();
}
