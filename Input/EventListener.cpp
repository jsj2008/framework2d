#include "EventListener.h"

EventListener::EventListener()
{
    //ctor
    g_InputManager.registerEvent(this,eUp);
    g_InputManager.registerEvent(this,eLeft);
    g_InputManager.registerEvent(this,eDown);
    g_InputManager.registerEvent(this,eRight);
}

EventListener::~EventListener()
{
    //dtor
}
