#include "FreeCamera.h"
#include <Input/InputState.h>
#include <Graphics/GraphicsManager.h>

FreeCamera::FreeCamera(InputState* inputState)
:EventListener(inputState)
{
    //ctor
    xPos = yPos = 0;
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
void FreeCamera::updateTransform(int xRes, int yRes)
{
    float xView = xRes / (2.0f * scale);
    float yView = yRes / (2.0f * scale);

    xTrans = -(xPos/scale) + xView;
    yTrans = -(yPos/scale) + yView;
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
            yPos--;
            return;
        }
        case eDown:
        {
            yPos++;
            return;
        }
        case eRight:
        {
            xPos++;
            return;
        }
        case eLeft:
        {
            xPos--;
            return;
        }
        case eInputActionsMax:
        {
            break;
        }
    }
}
