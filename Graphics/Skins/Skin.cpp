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
    glPushMatrix();
        glTranslatef(center.x,center.y,0);
        vRender();
    glPopMatrix();
}
