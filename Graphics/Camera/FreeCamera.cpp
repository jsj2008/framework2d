#include "FreeCamera.h"
#include <Graphics/GraphicsManager.h>
#include <Graphics/Camera/PhysicsCamera.h>
#include <Entities/Entity.h>
#include <Events/Events.h>

FreeCamera::FreeCamera()
:EventListener()
{
    //ctor
    scale = 15.0f;
    Events::global().registerListener(this, {eClearQueue|eBlockQueue});
    enableBias = false;
}

FreeCamera::~FreeCamera()
{
    //dtor
    g_InputManager.unregisterEvent(this,eUp);
    g_InputManager.unregisterEvent(this,eLeft);
    g_InputManager.unregisterEvent(this,eDown);
    g_InputManager.unregisterEvent(this,eRight);
    g_InputManager.unregisterEvent(this,ePlus);
    g_InputManager.unregisterEvent(this,eMinus);
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

    if (enableBias)
    {
        translation.x = -bias.x + xView;
        translation.y = -bias.y + yView;
    }
}
void FreeCamera::resetInput()
{
}

bool FreeCamera::trigger(ShowEntityEvent* _event) /// FIXME the maths here is wrong
{
    bias = _event->getEntity()->getPosition();
    enableBias = true;
    //g_GraphicsManager.setCamera(new PhysicsCamera(_event->getEntity()->getBody()));
    //delete this;
    return true;
}
void FreeCamera::trigger(InputActions action, bool _pressed)
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
