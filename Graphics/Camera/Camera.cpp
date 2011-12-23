#include "Camera.h"
#include <GL/gl.h>

Camera::Camera()
{
    //ctor
}

Camera::~Camera()
{
    //dtor
}

void Camera::updateView(Vec2i resolution)
{
    updateTransform(resolution);

    glLoadIdentity();
    glScalef(scale,scale,0);
    glTranslatef(translation.x,translation.y,0);

    view.x = (-translation.x)*scale;
    view.y = (-translation.y)*scale;
}

void Camera::registerActions()
{

}
