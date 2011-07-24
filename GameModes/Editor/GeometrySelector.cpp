#include "GeometrySelector.h"
#include <Graphics/GraphicsManager.h>
#include <Level/LevelManager.h>
#include <Physics/PhysicsManager.h>
#include <Input/InputManager.h>
#include <Graphics/Camera/FreeCamera.h>
#include <Box2D/Common/b2Math.h>
#include <Entities/AIEntity.h>

GeometrySelector::GeometrySelector(FreeCamera* camera)
{
    //ctor
    mouseJoint = nullptr;
    camera->activate();
    mCamera = camera;
    //g_InputManager.registerStateSelect(this,"GeometrySelector");
}

GeometrySelector::~GeometrySelector()
{
    //dtor
}

void GeometrySelector::start(unsigned char button)
{
    if (mouseJoint != nullptr)
    {
        mouseMove(startPos);
        activeMouseJoints.insert(mouseJoint);
        mouseJoint = nullptr;
    }
    else
    {
        Vec2f point = startPos.ScreenToWorldSpace();
        b2Body* body = g_PhysicsManager.select(point, nullptr);
        if (body != nullptr)
        {
            if (button == 1)
            {
                mouseJoint = g_PhysicsManager.createJoint(body,point);
                // This is code to prevent the attached body from dying
                AIEntity* entity = dynamic_cast<AIEntity*>((Entity*)body->GetUserData());
                if (entity != nullptr)
                {
                    bodyHealth = entity->health;
                    entity->health = pow(2,30);
                }
            }
            else if (button == 3)
            {
                bool mouseJointRemoved = false;
                for (b2JointEdge* edge = body->GetJointList(); edge != nullptr;)
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
                    g_LevelManager.removeBody(static_cast<Entity*>(body->GetUserData()));
                }
            }
        }
    }
}
void GeometrySelector::mouseMove(Vec2i mouse)
{
    if (mouseJoint != nullptr)
    {
        Vec2f point = mouse.ScreenToWorldSpace();
        mouseJoint->SetTarget(point);
        b2Body* body = mouseJoint->GetBodyB();
        Vec2f position = body->GetWorldCenter();
    }
}
void GeometrySelector::buttonUp(Vec2i mouse, unsigned char button)
{
    if (mouseJoint != nullptr)
    {
        AIEntity* entity = dynamic_cast<AIEntity*>((Entity*)(mouseJoint->GetBodyB()->GetUserData()));
        if (entity != nullptr)
            entity->health = bodyHealth;
        g_PhysicsManager.deleteJoint(mouseJoint);
        mouseJoint = nullptr;
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
    if (mouseJoint != nullptr)
    {
        Vec2f position = mouseJoint->GetAnchorA();
        glVertex2f(position.x,position.y);
        position = mouseJoint->GetAnchorB();
        glVertex2f(position.x,position.y);
    }
}


















