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
    float hw = width*0.5f;
    float hh = height*0.5f;
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2i(-hw,-hh);
    glTexCoord2f(1,0);
    glVertex2i(hw,-hh);
    glTexCoord2f(1,1);
    glVertex2i(hw,hh);
    glTexCoord2f(0,1);
    glVertex2i(-hw,hh);
    glEnd();
}
