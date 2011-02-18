#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
    public:
        Camera();
        virtual ~Camera();
        void updateView(int xRes, int yRes);
        int getViewX(){return viewX;}
        int getViewY(){return viewY;}
        float getPixelsPerMeter(){return scale;}
    protected:
        virtual void updateTransform(int xRes, int yRes)=0;
        float xTrans, yTrans, scale;
        int viewX, viewY;
    private:
};

#endif // CAMERA_H
