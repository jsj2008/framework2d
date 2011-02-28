#include "FontPrimitive.h"
#include <GL/gl.h>

FontPrimitive::FontPrimitive(const char* name, unsigned int _texture, const Vec2i _dimensions)
:myString(name)
{
    //ctor
    texture = _texture;
    dimensions = _dimensions;
}

FontPrimitive::~FontPrimitive()
{
    //dtor
}

void FontPrimitive::draw(const Vec2i topLeft)
{
    Vec2i bottomRight = topLeft + dimensions;
    glBindTexture(GL_TEXTURE_2D,texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2i(topLeft.x,topLeft.y);
    glTexCoord2f(0,1);
    glVertex2i(topLeft.x,bottomRight.y);
    glTexCoord2f(1,1);
    glVertex2i(bottomRight.x,bottomRight.y);
    glTexCoord2f(1,0);
    glVertex2i(bottomRight.x,topLeft.y);
    glEnd();
}
