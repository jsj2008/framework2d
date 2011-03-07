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

#include <iostream>
bool InputContext::activate(const CEGUI::EventArgs&)
{
    std::cout << "State switched " << this << std::endl;
    g_InputManager.setActiveEvent(this);
    if (mCamera != NULL)
    {
        g_GraphicsManager.setCamera(mCamera);
        mCamera->activate();
    }
    return true;
}
