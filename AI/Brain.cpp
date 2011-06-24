#include "Brain.h"
#include <cassert>
Brain::Brain()
{
    //ctor
    mEntity = NULL;
}

Brain::~Brain()
{
    //dtor
}

void Brain::setEntity(AIEntity* _Entity)
{
    assert(mEntity == NULL);
    mEntity = _Entity;
}
