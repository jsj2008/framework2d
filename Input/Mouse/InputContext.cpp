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

void InputContext::deactivate()
{
}
