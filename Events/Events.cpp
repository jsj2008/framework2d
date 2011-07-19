#include "Events.h"

Events::Events()
{
    //ctor
}

Events::~Events()
{
    //dtor
}

Events& Events::global()
{
    static Events events;
    return events;
}
