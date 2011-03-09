#include "ZombieBrain.h"
#include <Entities/AIEntity.h>

ZombieBrain::ZombieBrain()
{
    //ctor
}

ZombieBrain::~ZombieBrain()
{
    //dtor
}

void ZombieBrain::update()
{
    mEntity->walkLeft();
}
