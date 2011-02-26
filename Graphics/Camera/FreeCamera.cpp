#include "FreeCamera.h"
#include <Input/InputState.h>
#include <Graphics/GraphicsManager.h>

FreeCamera::FreeCamera(InputState* inputState)
:EventListener(inputState)
{
    //ctor
    if (inputState != NULL)
    {
        inputState->registerEvent(this,ePlus);
        inputState->registerEvent(this,eMinus);
    }
    else
    {
        g_InputManager.registerEvent(this,ePlus);
        g_InputManager.registerEvent(this,eMinus);
    }
    scale = 15.0f;
}

FreeCamera::~FreeCamera()
{
    //dtor
}
void FreeCamera::registerWithInputState(InputState* inputState)
{
    inputState->registerEvent(this,eUp);
    inputState->registerEvent(this,eLeft);
    inputState->registerEvent(this,eDown);
    inputState->registerEvent(this,eRight);
    inputState->registerEvent(this,ePlus);
    inputState->registerEvent(this,eMinus);
}
void FreeCamera::updateTransform(Vec2i resolution)
{
    float xView = resolution.x / (2.0f * scale);
    float yView = resolution.y / (2.0f * scale);

    xTrans = -(position.x/scale) + xView;
    yTrans = -(position.y/scale) + yView;
}
#include <iostream>
using namespace std;
void FreeCamera::trigger(InputActions action)
{
    switch (action)
    {
        case ePlus:
        {
            scale *= 1.1f;
            return;
        }
        case eMinus:
        {
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
