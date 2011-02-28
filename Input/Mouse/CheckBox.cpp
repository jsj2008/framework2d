#include "CheckBox.h"
#include <Graphics/GraphicsManager.h>
#include <Graphics/Primitives/FontPrimitive.h>
#include <GL/gl.h>
#define SIZE 25

CheckBox::CheckBox(const Vec2i position, const char* _text , bool initial)
:ClickReleaseEvent(Rect(position.x,position.y,position.x+SIZE,position.y+SIZE))
{
    //ctor
    checked = initial;
    text = g_GraphicsManager.renderFont(_text,-1);
}

CheckBox::~CheckBox()
{
    //dtor
}

void CheckBox::click(Vec2i mouse, unsigned char button)
{
    checked = !checked;
}

void CheckBox::render()
{
    glPushMatrix();
    glLoadIdentity();
    glBindTexture(GL_TEXTURE_2D,0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(mRect.x,mRect.y);
    glVertex2i(mRect.x2,mRect.y);
    glVertex2i(mRect.x2,mRect.y2);
    glVertex2i(mRect.x,mRect.y2);
    glEnd();
    if (checked)
        glColor3f(0,1,0);
    else
        glColor3f(1,0,0);
    glBegin(GL_QUADS);
    glVertex2i(mRect.x,mRect.y);
    glVertex2i(mRect.x2,mRect.y);
    glVertex2i(mRect.x2,mRect.y2);
    glVertex2i(mRect.x,mRect.y2);
    glEnd();
    glColor3f(1,1,1);
    text->draw(Vec2i(mRect.x,mRect.y));
    glPopMatrix();
}
