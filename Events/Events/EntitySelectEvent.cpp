#include "EntitySelectEvent.h"

EntitySelectEvent::EntitySelectEvent(Entity* _selectedEntity)
{
    //ctor
    selectedEntity = _selectedEntity;
}

EntitySelectEvent::~EntitySelectEvent()
{
    //dtor
}
