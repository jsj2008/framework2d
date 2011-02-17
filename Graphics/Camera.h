#ifndef CAMERA_H
#define CAMERA_H

class b2Body;
class Camera
{
    public:
        Camera(b2Body* _body);
        virtual ~Camera();
        virtual void updateView(int xRes, int yRes);
        int getViewX(){return viewX;}
        int getViewY(){return viewY;}
    protected:
    private:
        b2Body* body;
        int viewX, viewY;
};

#endif // CAMERA_H
