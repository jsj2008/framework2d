#include "BubbleSkin.h"
#include <GL/gl.h>

BubbleSkin::BubbleSkin(float _radius)
{
    //ctor
    radius = _radius;
}

BubbleSkin::~BubbleSkin()
{
    //dtor
}

void BubbleSkin::vRender()
{
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2i(-radius,-radius);
    glTexCoord2f(1,0);
    glVertex2i(radius,-radius);
    glTexCoord2f(1,1);
    glVertex2i(radius,radius);
    glTexCoord2f(0,1);
    glVertex2i(-radius,radius);
    glEnd();
}
