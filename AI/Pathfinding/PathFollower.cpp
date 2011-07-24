#include "PathFollower.h"
#include <AI/AIManager.h>
#include <AI/PathGeneration/PathSegment.h>
#include <AI/PathGeneration/PathNodeDynamic.h>
#include <Box2D/Box2D.h>

PathFollower::PathFollower()
{
    //ctor
    closest = Node(0,0);
}

PathFollower::~PathFollower()
{
    //dtor
}

AIManager::Operation PathFollower::update(const Vec2f& _position, Node newTarget)
{
    Node newClosest = g_AIManager.findClosestNode(_position); // FIXME optimise this so it checks the distance first
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
                if (_position.x < instruction.target.x)
                {
                    instructions.pop();
                }
                break;
            }
            case AIManager::eJumpRight:
            case AIManager::eWalkRight:
            {
                if (_position.x > instruction.target.x)
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



































