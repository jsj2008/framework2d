#include "Camera.h"
#include <GL/gl.h>

Camera::Camera()
{
    //ctor
    viewX = viewY = 0;
}

Camera::~Camera()
{
    //dtor
}

void Camera::updateView(int xRes, int yRes)
{
    updateTransform(xRes,yRes);

    glLoadIdentity();
    glScalef(scale,scale,0);
    glTranslatef(xTrans,yTrans,0);

    viewX = (-xTrans)*scale;
    viewY = (-yTrans)*scale;
}
