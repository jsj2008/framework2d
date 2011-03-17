#include "PathFollower.h"
#include <AI/AIManager.h>
#include <AI/PathGeneration/PathSegment.h>
#include <AI/PathGeneration/PathNodeDynamic.h>
#include <Box2D/Box2D.h>

PathFollower::PathFollower()
{
    //ctor
    closest = Node(NULL,0);
}

PathFollower::~PathFollower()
{
    //dtor
}

AIManager::Operation PathFollower::update(b2Body* body, Node newTarget)
{
    const Vec2f& position = body->GetPosition();
    Node newClosest = g_AIManager.findClosestNode(position); // FIXME optimise this so it checks the distance first
    if (newClosest != closest || newTarget != target)
    {
        target = newTarget;
        closest = newClosest;
        calculateNewPath();
    }
    if (!instructions.empty())
    {
        AIManager::PathInstruction& instruction = instructions.top();
        switch (instruction.operation)
        {
            case AIManager::eStandStill:
            {
                break;
            }
            case AIManager::eJumpLeft:
            case AIManager::eWalkLeft:
            {
                if (position.x < instruction.target.x)
                {
                    instructions.pop();
                }
                break;
            }
            case AIManager::eJumpRight:
            case AIManager::eWalkRight:
            {
                if (position.x > instruction.target.x)
                {
                    instructions.pop();
                }
                break;
            }
            case AIManager::eOperationsMax:
            default:
            {
                throw -1;
            }
        }
        return instruction.operation;
    }
    else return AIManager::eStandStill;
}
void PathFollower::calculateNewPath()
{
    while (!instructions.empty())
    {
        instructions.pop();
    }
    g_AIManager.path(closest,target,instructions);
}



































