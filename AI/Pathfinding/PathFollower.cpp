#include "PathFollower.h"
#include <AI/AIManager.h>
#include <AI/Pathfinding/PathSegment.h>
#include <AI/Pathfinding/PathNode.h>

PathFollower::PathFollower()
{
    //ctor
    closest = NULL;
}

PathFollower::~PathFollower()
{
    //dtor
}

PathFollower::Operation PathFollower::update(const Vec2f& position)
{
    PathSegment* newClosest = g_AIManager.findClosestPath(position);
    if (newClosest != closest)
    {
        closest = newClosest;
        calculateNewPath();
    }
    PathInstruction tempInstruction;
    tempInstruction.segment = closest;
    //tempInstruction.operation = (tempWalkingLeft)? eWalkLeft:eWalkRight;
    //tempInstruction.target = (tempWalkingLeft)? closest->getNodeA()->getPosition():closest->getNodeB()->getPosition();
    PathInstruction& instruction = instructions.front();
    switch (instruction.operation)
    {
        case eWalkLeft:
        {
            if (position.x < instruction.target.x)
            {
                instructions.pop();
                instructions.push(instruction);
                instruction = instructions.front();
            }
            break;
        }
        case eWalkRight:
        {
            if (position.x > instruction.target.x)
            {
                instructions.pop();
                instructions.push(instruction);
                instruction = instructions.front();
            }
            break;
        }
        case eOperationsMax:
        default:
        {
            throw -1;
        }
    }
    return instruction.operation;
}
void PathFollower::calculateNewPath()
{
    while (!instructions.empty())
    {
        instructions.pop();
    }
    PathInstruction tempInstruction;
    tempInstruction.segment = closest;
    tempInstruction.operation = eWalkLeft;
    tempInstruction.target = closest->getNodeA()->getPosition();
    instructions.push(tempInstruction);
    tempInstruction.operation = eWalkRight;
    tempInstruction.target = closest->getNodeB()->getPosition();
    instructions.push(tempInstruction);
    loop = true;
}






































