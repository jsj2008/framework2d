#include "DebugDraw.h"
#include <GL/gl.h>

DebugDraw::DebugDraw()
{
    //ctor
    SetFlags(e_jointBit|e_shapeBit/*|e_aabbBit/|e_pairBit*/|e_centerOfMassBit);
}

DebugDraw::~DebugDraw()
{
    //dtor
}

/// Draw a closed polygon provided in CCW order.
void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    glColor3f(color.r,color.g,color.b);
    glBegin(GL_LINE_LOOP);
    for (int32 i = 0; i < vertexCount; i++)
    {
        glVertex2f(vertices[i].x,vertices[i].y);
    }
    glEnd();
}

/// Draw a solid closed polygon provided in CCW order.
void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    glColor3f(color.r,color.g,color.b);
    glBegin(GL_TRIANGLE_FAN);
    for (int32 i = 0; i < vertexCount; i++)
    {
        glVertex2f(vertices[i].x,vertices[i].y);
    }
    glEnd();
}

/// Draw a circle.
void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    glColor3f(color.r,color.g,color.b);
    glBegin(GL_LINES);

    glVertex2f(center.x,center.y);
    glVertex2f(center.x,center.y+radius);

    glVertex2f(center.x,center.y);
    glVertex2f(center.x,center.y-radius);

    glVertex2f(center.x,center.y);
    glVertex2f(center.x+radius,center.y);

    glVertex2f(center.x,center.y);
    glVertex2f(center.x-radius,center.y);

    glEnd();
}

/// Draw a solid circle.
void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    glColor3f(color.r,color.g,color.b);
    glBegin(GL_LINES);

    glVertex2f(center.x,center.y);
    glVertex2f(center.x,center.y+radius);

    glVertex2f(center.x,center.y);
    glVertex2f(center.x,center.y-radius);

    glVertex2f(center.x,center.y);
    glVertex2f(center.x+radius,center.y);

    glVertex2f(center.x,center.y);
    glVertex2f(center.x-radius,center.y);

    glEnd();
}

/// Draw a line segment.
void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    glColor3f(color.r,color.g,color.b);
    glBegin(GL_LINES);
    glVertex2f(p1.x,p1.y);
    glVertex2f(p2.x,p2.y);
    glEnd();
}

/// Draw a transform. Choose your own length scale.
/// @param xf a transform.
void DebugDraw::DrawTransform(const b2Transform& xf)
{

}
