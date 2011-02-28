#include "Icon.h"
#include <Graphics/Contexts/MaterialContext.h>
#include <Graphics/GraphicsManager.h>
#include <GL/gl.h>
#include <string>


Icon::Icon(const char* iconName, const Vec2i _dimensions)
{
    //ctor
    dimensions = _dimensions;
    std::string filename("Icons/");
    filename.append(iconName);
    materialContext = g_GraphicsManager.getMaterial(filename.c_str());
}

Icon::~Icon()
{
    //dtor
    materialContext->release();
}

void Icon::draw(const Vec2i topLeft)
{
    Vec2i bottomRight = topLeft + dimensions;
    materialContext->bind();
    glColor3f(1,1,1);
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
