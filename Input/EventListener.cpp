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
    /*g_InputManager.unregisterEvent(this,eUp);
    g_InputManager.unregisterEvent(this,eLeft);
    g_InputManager.unregisterEvent(this,eDown);
    g_InputManager.unregisterEvent(this,eRight);*/
}
