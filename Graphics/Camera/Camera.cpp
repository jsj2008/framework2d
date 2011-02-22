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
    glTranslatef(xTrans,yTrans,0);

    view.x = (-xTrans)*scale;
    view.y = (-yTrans)*scale;
}
