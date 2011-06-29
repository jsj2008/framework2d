#include "Brain.h"
#include <cassert>
Brain::Brain()
{
    //ctor
    mEntity = nullptr;
}

Brain::~Brain()
{
    //dtor
}

void Brain::setEntity(AIEntity* _Entity)
{
    assert(mEntity == nullptr);
    mEntity = _Entity;
}
