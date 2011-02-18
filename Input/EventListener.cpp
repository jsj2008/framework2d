#include "EventListener.h"

EventListener::EventListener(InputState* inputState)
{
    //ctor
    if (inputState != NULL)
    {
        inputState->registerEvent(this,eUp);
        inputState->registerEvent(this,eLeft);
        inputState->registerEvent(this,eDown);
        inputState->registerEvent(this,eRight);
    }
    else
    {
        g_InputManager.registerEvent(this,eUp);
        g_InputManager.registerEvent(this,eLeft);
        g_InputManager.registerEvent(this,eDown);
        g_InputManager.registerEvent(this,eRight);
    }
}

EventListener::~EventListener()
{
    //dtor
}
