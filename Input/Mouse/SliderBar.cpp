#include "SliderBar.h"
#include <Graphics/GraphicsManager.h>
#include <Graphics/Primitives/FontPrimitive.h>
#define HEIGHT 10
SliderBar::SliderBar(const Vec2i& left, int width, const char* name, float initialPosition)
:ClickDragEvent(Rect(left.x,left.y,left.x+width,left.y+HEIGHT))
{
    //ctor
    positionf = initialPosition;
    length = width;
    mText = g_GraphicsManager.renderFont(name,-1);
    Vec2i dimensions(mRect.x2-mRect.x,mRect.y2-mRect.y);
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
    positioni = positionf*length;
}
#include <GL/gl.h>
void SliderBar::render()
{
    glPushMatrix();
    glLoadIdentity();
    glBegin(GL_LINES);
    glVertex2i(mRect.x,mRect.y+(HEIGHT/2));
    glVertex2i(mRect.x2,mRect.y+(HEIGHT/2));
    glEnd();
    glBegin(GL_POINTS);
    glVertex2i(mRect.x,mRect.y+(HEIGHT/2));
    glVertex2i(mRect.x2,mRect.y+(HEIGHT/2));
    glVertex2i(mRect.x+positioni,mRect.y+(HEIGHT/2));
    glEnd();
    Vec2i topLeft(mRect.x,mRect.y);
    mText->draw(topLeft);
    glPopMatrix();
}
