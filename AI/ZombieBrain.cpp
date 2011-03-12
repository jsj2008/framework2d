#include "ZombieBrain.h"
#include <Entities/AIEntity.h>
#include <AI/Pathfinding/PathFollower.h>
#include <AI/AIManager.h>

ZombieBrain::ZombieBrain()
{
    //ctor
    follower = new PathFollower();
}

ZombieBrain::~ZombieBrain()
{
    //dtor
}

void ZombieBrain::update()
{
    PathFollower::Operation operation = follower->update(mEntity->mBody, g_AIManager.getPlayerSegment());
    if (operation == PathFollower::Operation::eWalkLeft)
    {
        mEntity->walkLeft();
    }
    else
    {
        mEntity->walkRight();
    }
}
