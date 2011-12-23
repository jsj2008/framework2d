#ifndef CAMERA_H
#define CAMERA_H

#include <GameObject.h>
#include <Types/Vec2i.h>

class Camera : public GameObject<Camera>
{
    public:
        Camera();
        virtual ~Camera();
        static void registerActions();
        void updateView(Vec2i resolution);
        const Vec2i& getView(){return view;}
        float getPixelsPerMeter(){return scale;}
        const Vec2f& getTranslation(){return translation;}
        virtual void activate()=0;
        void registerDeathListener(void*){throw -1;}
    protected:
        virtual void updateTransform(Vec2i resolution)=0;
        Vec2f translation;
        float scale;
        Vec2i view;
    private:
};

#endif // CAMERA_H
