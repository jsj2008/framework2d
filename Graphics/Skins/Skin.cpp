#include "Skin.h"
#include <GL/gl.h>
#include <Box2D/Box2D.h>
#include <Graphics/Contexts/MaterialContext.h>
#define M_PI 3.14159265358979323846
Skin::Skin()
{
    //ctor
    program = 0;
    material = NULL;
}

Skin::~Skin()
{
    //dtor
    material->release();
}

void Skin::render(b2Body* body)
{
    material->bindTexture();
    //glUseProgram(0);
    const Vec2f & center = body->GetWorldCenter();
    float rotation = -body->GetAngle();
    glPushMatrix();
        glTranslatef(center.x,center.y,0);
        if (rotation != 0.0f)
            glRotatef(rotation*(180.0/M_PI),0,0,-1);
        vRender();
    glPopMatrix();
}
