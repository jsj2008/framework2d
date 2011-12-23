#include "GeometrySelector.h"
#include <Graphics/GraphicsManager.h>
#include <Physics/BodyPart.h>
#include <Physics/PhysicsManager.h>
#include <Input/InputManager.h>
#include <Graphics/Camera/FreeCamera.h>
#include <Box2D/Common/b2Math.h>
#include <Entities/AIEntity.h>
#include <GameModes/Editor/Undo/UndoStack.h>
#include <GameModes/Editor/Undo/Entries/EntityDeleteEntry.h>
#include <GameModes/Editor/EditorMode.h>
#include <Events/Events.h>
#include <Events/Events/EntitySelectEvent.h>

GeometrySelector::GeometrySelector(FreeCamera* camera, EditorMode* _editorMode)
{
    //ctor
    mouseJoint = nullptr;
    camera->activate();
    mCamera = camera;
    editorMode = _editorMode;
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
        b2Body* body = editorMode->getActiveWorld()->select(point, nullptr);
        if (body != nullptr)
        {
            if (button == 1)
            {
                mouseJoint = editorMode->getActiveWorld()->createJoint(body,point);
                Entity* entity = nullptr; /// FIXME body->getBodyPart()->getEntity();
                EntitySelectEvent event(entity);
                Events::global().triggerEvent(&event);
                // This is code to prevent the attached body from dying
                AIEntity* castEntity = dynamic_cast<AIEntity*>(entity);
                if (castEntity != nullptr)
                {
                    bodyHealth = castEntity->health;
                    castEntity->health = pow(2,30);
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
                        editorMode->getActiveWorld()->deleteJoint(joint);
                        mouseJointRemoved = true;
                        break;
                    }
                }
                if (!mouseJointRemoved)
                {
                    //UndoStack::global().addEntry(new EntityDeleteEntry(body->getBodyPart()->getEntity(), editorMode->getActiveLevel()));
                    ///FIXME put me back in
                    //g_LevelManager.getLevel()->removeBody(static_cast<Entity*>(body->GetUserData()));
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
    }
}
void GeometrySelector::buttonUp(Vec2i mouse, unsigned char button)
{
    if (mouseJoint != nullptr)
    {
        AIEntity* entity = nullptr; //dynamic_cast<AIEntity*>(mouseJoint->GetBodyB()->getBodyPart()->getEntity());
        if (entity != nullptr)
            entity->health = bodyHealth;
        editorMode->getActiveWorld()->deleteJoint(mouseJoint);
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


















