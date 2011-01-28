#ifndef CAMERA_H
#define CAMERA_H

class b2Body;
class Camera
{
    public:
        Camera(b2Body* _body);
        virtual ~Camera();
        virtual void updateView(int xRes, int yRes);
    protected:
    private:
        b2Body* body;
};

#endif // CAMERA_H
