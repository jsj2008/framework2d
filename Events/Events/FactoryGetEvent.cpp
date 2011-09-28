#include "FactoryGetEvent.h"
#include <iostream>
FactoryGetEvent::FactoryGetEvent(const std::string& _name)
{
    //ctor
    name = _name;
    std::cout << "Got: " << name << std::endl;
}

FactoryGetEvent::~FactoryGetEvent()
{
    //dtor
}
