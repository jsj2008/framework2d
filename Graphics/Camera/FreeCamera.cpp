#include "FreeCamera.h"
#include <Graphics/GraphicsManager.h>

FreeCamera::FreeCamera()
:EventListener()
{
    //ctor
    g_InputManager.registerEvent(this,ePlus);
    g_InputManager.registerEvent(this,eMinus);
    scale = 15.0f;
}

FreeCamera::~FreeCamera()
{
    //dtor
}
void FreeCamera::activate()
{
    g_InputManager.registerEvent(this,eUp);
    g_InputManager.registerEvent(this,eLeft);
    g_InputManager.registerEvent(this,eDown);
    g_InputManager.registerEvent(this,eRight);
    g_InputManager.registerEvent(this,ePlus);
    g_InputManager.registerEvent(this,eMinus);
}
void FreeCamera::updateTransform(Vec2i resolution)
{
    float xView = resolution.x / (2.0f * scale);
    float yView = resolution.y / (2.0f * scale);

    translation.x = -(position.x/scale) + xView;
    translation.y = -(position.y/scale) + yView;
}
void FreeCamera::resetInput()
{

}
void FreeCamera::trigger(InputActions action)
{
    switch (action)
    {
        case ePlus:
        {
            if (scale < 60.0f)
                scale *= 1.1f;
            return;
        }
        case eMinus:
        {
            if (scale > 4.0f)
                scale /= 1.1f;
            return;
        }
        case eUp:
        {
            position.y-=15;
            return;
        }
        case eDown:
        {
            position.y+=15;
            return;
        }
        case eRight:
        {
            position.x+=15;
            return;
        }
        case eLeft:
        {
            position.x-=15;
            return;
        }
        case eInputActionsMax:
        {
            break;
        }
    }
}
