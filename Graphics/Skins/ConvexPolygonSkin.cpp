#include "ConvexPolygonSkin.h"
#include <cstring>
#include <GL/gl.h>

ConvexPolygonSkin::ConvexPolygonSkin(Vec2f *_points, unsigned char _numPoints)
{
    //ctor
    numPoints = _numPoints;
    memcpy(points,_points,sizeof(Vec2f)*numPoints);
}

ConvexPolygonSkin::~ConvexPolygonSkin()
{
    //dtor
}

void ConvexPolygonSkin::vRender()
{
    glBegin(GL_TRIANGLE_FAN);
    for (unsigned char i = 0; i < numPoints; i++)
    {
        glVertex2f(points[i].x,points[i].y);
    }
    glEnd();
}
