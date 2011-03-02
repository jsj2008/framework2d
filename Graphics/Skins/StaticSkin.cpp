#include "StaticSkin.h"
#include <GL/gl.h>

StaticSkin::StaticSkin(int _width, int _height)
{
    //ctor
    width = _width;
    height = _height;
}

StaticSkin::~StaticSkin()
{
    //dtor
}

void StaticSkin::vRender()
{
    glPushMatrix();
    glScalef(0.001f,0.001f,1);
    float hw = width*500.f;
    float hh = height*500.f;
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0,0);
    glVertex2f(-hw,-hh);
    glTexCoord2f(1,0);
    glVertex2f(hw,-hh);
    glTexCoord2f(1,1);
    glVertex2f(hw,hh);
    glTexCoord2f(0,1);
    glVertex2f(-hw,hh);
    glEnd();
    glPopMatrix();
}
