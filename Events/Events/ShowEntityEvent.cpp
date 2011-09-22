#include "ShowEntityEvent.h"

ShowEntityEvent::ShowEntityEvent(Entity* _entity)
{
    //ctor
    entity = _entity;
}

ShowEntityEvent::~ShowEntityEvent()
{
    //dtor
}
