#include "Brain.h"
#include <cassert>
#define NULL 0
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
