#include "Camera.h"
#include <GL/gl.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Graphics/GraphicsManager.h>

Camera::Camera(b2Body* _body)
{
    //ctor
    body = _body;
    viewX = viewY = 0;
}

Camera::~Camera()
{
    //dtor
}
void Camera::updateView(int xRes, int yRes)
{
    float xView = xRes / (2.0f * PIXELS_PER_METER);
    float yView = yRes / (2.0f * PIXELS_PER_METER);

    glLoadIdentity();
    b2Vec2 center = body->GetWorldCenter();
    glScalef(PIXELS_PER_METER,PIXELS_PER_METER,0);
    glTranslatef(-center.x + xView,-center.y + yView,0);

    viewX = (center.x - xView)*PIXELS_PER_METER;
    viewY = (center.y - yView)*PIXELS_PER_METER;
}
