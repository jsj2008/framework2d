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
    AIManager::Operation operation = follower->update(mEntity->getPosition(), g_AIManager.getPlayerNode());
    switch (operation)
    {
        /*case AIManager::Operation::eStandStill:
        {
            mEntity->stopWalking();
            break;
        }
        case AIManager::Operation::eWalkLeft:
        {
            mEntity->walkLeft();
            break;
        }
        case AIManager::Operation::eWalkRight:
        {
            mEntity->walkRight();
            break;
        }
        case AIManager::Operation::eJumpLeft:
        {
            mEntity->walkLeft();
            mEntity->jump();
            break;
        }
        case AIManager::Operation::eJumpRight:
        {
            mEntity->walkRight();
            mEntity->jump();
            break;
        }
        case AIManager::Operation::eOperationsMax:*/
        default:
            throw -1;
    }
}
