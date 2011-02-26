#include "BubbleSkin.h"
#include <GL/gl.h>

BubbleSkin::BubbleSkin()
{
    //ctor
}

BubbleSkin::~BubbleSkin()
{
    //dtor
}

void BubbleSkin::vRender()
{
    glBegin(GL_POINTS);
    glVertex2f(0,0);
    glEnd();
}
