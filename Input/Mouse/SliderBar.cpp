#include "SliderBar.h"
#include <Graphics/GraphicsManager.h>
#include <Graphics/Primitives/FontPrimitive.h>

SliderBar::SliderBar(const Vec2i& left, int width, const char* name, float initialPosition)
:ClickDragEvent(Rect(left.x,left.y+16,left.x+width,left.y+46))
{
    //ctor
    positionf = initialPosition;
    length = width;
    mText = g_GraphicsManager.renderFont(name,-1);
}

SliderBar::~SliderBar()
{
    //dtor
}

void SliderBar::start(unsigned char button)
{
    calculatePosition(startPos.x);
}
void SliderBar::mouseMove(Vec2i mouse)
{
    calculatePosition(mouse.x);
}
void SliderBar::buttonUp(Vec2i mouse, unsigned char button)
{
    calculatePosition(mouse.x);
}

void SliderBar::calculatePosition(int mousePosition)
{
    float left = mRect.x;
    float right = mRect.x2;
    float length = right - left;
    float distance = float(mousePosition) - left;
    positionf = distance/length;
    if (positionf > 1.0f) positionf = 1.0f;
    else if (positionf < 0.0f) positionf = 0.0f;
    positioni = positionf*length;
}
#include <GL/gl.h>
void SliderBar::render()
{
    glPushMatrix();
    glLoadIdentity();
    glBegin(GL_LINES);
    glVertex2i(mRect.x,mRect.y+16);
    glVertex2i(mRect.x2,mRect.y+16);
    glEnd();
    glBegin(GL_POINTS);
    glVertex2i(mRect.x,mRect.y+16);
    glVertex2i(mRect.x2,mRect.y+16);
    glVertex2i(mRect.x+positioni,mRect.y+16);
    glEnd();
    Vec2i topLeft(mRect.x,mRect.y);
    mText->draw(topLeft);
    glPopMatrix();
}
