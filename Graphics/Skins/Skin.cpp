#include "Skin.h"
#include <GL/gl.h>
#include <Box2D/Box2D.h>
#include <Graphics/Contexts/MaterialContext.h>
#include <Physics/Body.h>
#define M_PI 3.14159265358979323846
Skin::Skin()
{
    //ctor
    material = nullptr;
}

Skin::~Skin()
{
    //dtor
    material->release();
}

void Skin::render(Body* body)
{
    material->bind();
    const Vec2f & center = body->getPosition();
    float rotation = -body->getAngle();
    glPushMatrix();
        glTranslatef(center.x,center.y,0);
        if (rotation != 0.0f)
            glRotatef(rotation*(180.0/M_PI),0,0,-1);
        vRender();
    glPopMatrix();
}

void Skin::registerActions()
{

}
