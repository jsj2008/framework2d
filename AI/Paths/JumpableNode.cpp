#include "JumpableNode.h"
#include <AI/Paths/PathfindingAlgorithm.h>

JumpableNode::JumpableNode(const Vec2f& _position)
:PathNode(_position)
{
    //ctor
}

JumpableNode::~JumpableNode()
{
    //dtor
}

void JumpableNode::path(PathfindingAlgorithm* algorithm, float distanceTravelled, NodeReference me)
{
    algorithm->add(target,distanceTravelled+1.0f,me,jumpDirection);
    algorithm->add(previous,distanceTravelled+1.0f,me,walkDirection);
}

void JumpableNode::setNeighbours(NodeReference _target, NodeReference _previous, AIManager::Operation _jumpDirection)
{
    target = _target;
    previous = _previous;
    jumpDirection = _jumpDirection;
    if (jumpDirection == AIManager::eJumpRight)
    {
        walkDirection = AIManager::eWalkLeft;
    }
    if (jumpDirection == AIManager::eJumpLeft)
    {
        walkDirection = AIManager::eWalkRight;
    }
}
