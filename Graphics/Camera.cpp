#include "Camera.h"
#include <GL/gl.h>
#include <Box2D/Dynamics/b2Body.h>

Camera::Camera(b2Body* _body)
{
    //ctor
    body = _body;
}

Camera::~Camera()
{
    //dtor
}

void Camera::updateView(int xRes, int yRes)
{
    xRes /= 2;
    yRes /= 2;
    //xRes = yRes = 0;
    glLoadIdentity();
    const b2Vec2 & center = body->GetWorldCenter();
    glTranslatef(-center.x + xRes,-center.y + yRes,0);
}
