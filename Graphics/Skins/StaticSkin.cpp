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
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2i(0,0);
    glTexCoord2f(1,0);
    glVertex2i(width,0);
    glTexCoord2f(1,1);
    glVertex2i(width,height);
    glTexCoord2f(0,1);
    glVertex2i(0,height);
    glEnd();
}
