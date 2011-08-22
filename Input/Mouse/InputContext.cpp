#include "InputContext.h"
#include <Graphics/GraphicsManager.h>
#include <Graphics/Camera/FreeCamera.h>
#include <Input/InputManager.h>

InputContext::InputContext()
{
    //ctor
}

InputContext::~InputContext()
{
    //dtor
}

void InputContext::changeResolution(Vec2i newResolution)
{
}

bool InputContext::activate(const CEGUI::EventArgs&)
{
    g_InputManager.setActiveEvent(this);
    if (mCamera != nullptr)
    {
        g_GraphicsManager.setCamera(mCamera);
        mCamera->activate();
    }
    return true;
}
