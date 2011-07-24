#include "PointGeometryMode.h"
#include <Types/TypeTable.h>

PointGeometryMode::PointGeometryMode(FactoryParameters* _params)
:DynamicEditorMode(_params)
{
    //ctor
}

PointGeometryMode::~PointGeometryMode()
{
    //dtor
}

void PointGeometryMode::buttonDown(Vec2i mouse, unsigned char button)
{
}
void PointGeometryMode::mouseMove(Vec2i mouse)
{
}
void PointGeometryMode::buttonUp(Vec2i mouse, unsigned char button)
{
    if (button == 1 && points.size() < b2_maxPolygonVertices)
    {
        Vec2f point = mouse.ScreenToWorldSpace();
        points.push_back(point);
    }
    if (points.size() == b2_maxPolygonVertices || button == 3)
    {
        if (points.size() > 2)
        {
            if (sort())
            {
                create();
            }
        }
        //def.numVertices = 0;
        points.clear();
    }
}
void PointGeometryMode::finish()
{
    typeTable->addValue("points",points);
}

#include <GL/gl.h>
void PointGeometryMode::render()
{
    if (points.size() > 0)
    {
        glBegin(GL_POINTS);
        glVertex2f(points[0].x,points[0].y);
        glEnd();
        glBegin(GL_LINE_STRIP);
        for (unsigned char i = 0; i < points.size(); i++)
        {
            glVertex2f(points[i].x,points[i].y);
        }
        glEnd();
    }
}

#define M_PI 3.14159265358979323846
bool PointGeometryMode::sort()
{
    bool alreadySorted = false;
    for (unsigned char i = 0; i < points.size(); i++)
    {
        Vec2f start = points[i%points.size()];
        Vec2f middle = points[(i+1)%points.size()];
        Vec2f end = points[(i+2)%points.size()];
        Vec2f a = start - middle;
        Vec2f b = end - middle;
        a.Normalize();
        b.Normalize();

        float myAngle = atan2(a.y,a.x);
        float tAngle = atan2(b.y,b.x);
        float angle = myAngle - tAngle;
        if (angle <= -M_PI)
        {
            angle += M_PI*2.0;
        }
        if (angle >= M_PI)
        {
            angle -= M_PI*2.0;
        }
        angle *= 180/M_PI;
        if (angle < 0.0f)
        {
            if (alreadySorted)
            {
                return false;
            }
            else
            {
                for (unsigned char ii = 0; ii < points.size()/2; ii++)
                {
                    Vec2f temp = points[ii];
                    points[ii] = points[points.size()-(ii+1)];
                    points[points.size()-(ii+1)] = temp;
                }
                alreadySorted = true;
                i = 0;
            }
        }
    }
    return true;
}

