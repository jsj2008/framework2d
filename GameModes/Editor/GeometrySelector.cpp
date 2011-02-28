#include "GeometrySelector.h"
#include <Graphics/GraphicsManager.h>
#include <Level/LevelManager.h>
#include <Physics/PhysicsManager.h>
#include <Box2D/Common/b2Math.h>

GeometrySelector::GeometrySelector(const Rect& _Rect)
:ClickDragEvent(_Rect)
{
    //ctor
    joint = NULL;
}

GeometrySelector::~GeometrySelector()
{
    //dtor
}

void GeometrySelector::start(unsigned char button)
{
    if (joint != NULL)
    {
        mouseMove(startPos);
        activeMouseJoints.insert(joint);
        joint = NULL;
    }
    else
    {
        Vec2f point = startPos.ScreenToWorldSpace();
        b2Body* body = g_PhysicsManager.select(point);
        if (body != NULL)
        {
            if (button == 1)
            {
                joint = g_PhysicsManager.createJoint(body,point);
            }
            else
            {
                bool mouseJointRemoved = false;
                for (b2JointEdge* edge = body->GetJointList(); edge != NULL;)
                {
                    b2Joint* joint = edge->joint;
                    edge = edge->next;
                    if (joint->GetType() == e_mouseJoint)
                    {
                        activeMouseJoints.erase((b2MouseJoint*)joint);
                        g_PhysicsManager.deleteJoint(joint);
                        mouseJointRemoved = true;
                        break;
                    }
                }
                if (!mouseJointRemoved)
                {
                    g_LevelManager.removeBody(body);
                }
            }
        }
    }
}
void GeometrySelector::mouseMove(Vec2i mouse)
{
    if (joint != NULL)
    {
        Vec2f point = mouse.ScreenToWorldSpace();
        joint->SetTarget(point);
        b2Body* body = joint->GetBodyB();
        Vec2f position = body->GetWorldCenter();
    }
}
void GeometrySelector::buttonUp(Vec2i mouse, unsigned char button)
{
    if (joint != NULL)
    {
        g_PhysicsManager.deleteJoint(joint);
        joint = NULL;
    }
}
#include <GL/gl.h>
void GeometrySelector::render()
{
    glColor3f(0,0,1);
    glBegin(GL_LINES);
    drawMouseJoints();
    glEnd();
    glBegin(GL_POINTS);
    drawMouseJoints();
    glEnd();
    glColor3f(1,1,1);
}
void GeometrySelector::drawMouseJoints()
{
    for (auto i = activeMouseJoints.begin(); i != activeMouseJoints.end(); i++)
    {
        Vec2f position = (*i)->GetAnchorA();
        glVertex2f(position.x,position.y);
        position = (*i)->GetAnchorB();
        glVertex2f(position.x,position.y);
    }
    if (joint != NULL)
    {
        Vec2f position = joint->GetAnchorA();
        glVertex2f(position.x,position.y);
        position = joint->GetAnchorB();
        glVertex2f(position.x,position.y);
    }
}



















