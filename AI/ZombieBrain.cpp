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
#define PRINT(x)// if (lastOperation != operation){lastOperation = operation; x; }
#include <iostream>
using namespace std;
void ZombieBrain::update()
{
    AIManager::Operation operation = follower->update(mEntity->mBody, g_AIManager.getPlayerNode());
    switch (operation)
    {
        case AIManager::Operation::eStandStill:
        {
            mEntity->stopWalking();
            PRINT(cout << "Stand still\n");
            break;
        }
        case AIManager::Operation::eWalkLeft:
        {
            mEntity->walkLeft();
            PRINT(cout << "walk left\n";)
            break;
        }
        case AIManager::Operation::eWalkRight:
        {
            mEntity->walkRight();
            PRINT(cout << "walk right\n";)
            break;
        }
        case AIManager::Operation::eJumpLeft:
        {
            mEntity->walkLeft();
            PRINT(cout << "jump left\n";)
            mEntity->jump();
            break;
        }
        case AIManager::Operation::eJumpRight:
        {
            mEntity->walkRight();
            mEntity->jump();
            PRINT(cout << "jump right\n";)
            break;
        }
        default:
            throw -1;
    }
}
