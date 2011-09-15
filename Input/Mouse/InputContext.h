#ifndef InputContext_H
#define InputContext_H

#include <CEGUI/CEGUI.h>
#include <Types/Vec2i.h>
class Camera;
class InputContext
{
    public:
        InputContext();
        virtual ~InputContext();
        virtual void init(){}
        virtual void render(){}
        virtual void buttonDown(Vec2i mouse, unsigned char button)=0;
        virtual void mouseMove(Vec2i mouse)=0;
        virtual void buttonUp(Vec2i mouse, unsigned char button)=0;
        virtual void changeResolution(Vec2i newResolution);
        virtual void deactivate();
        virtual bool activate(const CEGUI::EventArgs& args);
    protected:
        Camera* mCamera;
    private:
};

#endif // InputContext_H
