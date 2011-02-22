#ifndef CAMERA_H
#define CAMERA_H

#include <Types/Vec2i.h>
class Camera
{
    public:
        Camera();
        virtual ~Camera();
        void updateView(Vec2i resolution);
        const Vec2i& getView(){return view;}
        float getPixelsPerMeter(){return scale;}
    protected:
        virtual void updateTransform(Vec2i resolution)=0;
        float xTrans, yTrans, scale;
        Vec2i view;
    private:
};

#endif // CAMERA_H
