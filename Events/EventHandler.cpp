#include "EventHandler.h"
#include <Events/EventListener.h>

void EventHandler::privateTrigger(Event* event)
{
    if (listener != nullptr)
    {
        listener->trigger(event);
    }
}
void EventHandler::privateRegisterListener(EventsListener* _listener)
{
    listener = _listener;
}
