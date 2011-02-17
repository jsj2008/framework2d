#include "Skin.h"
#include <GL/gl.h>
#include <Box2D/Box2D.h>
#include <Graphics/Contexts/TextureContext.h>

Skin::Skin()
{
    //ctor
    program = 0;
    texture = NULL;
}

Skin::~Skin()
{
    //dtor
    texture->release();
}

void Skin::render(b2Body* body)
{
    texture->bindTexture();
    //glUseProgram(0);
    const b2Vec2 & center = body->GetWorldCenter();
    float rotation = -body->GetAngle();
    glPushMatrix();
        glTranslatef(center.x,center.y,0);
        if (rotation != 0.0f)
            glRotatef(rotation*(180.0/M_PI),0,0,-1);
        vRender();
    glPopMatrix();
}
