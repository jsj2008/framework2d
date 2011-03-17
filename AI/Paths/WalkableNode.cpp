#include "WalkableNode.h"
#include <AI/Paths/PathfindingAlgorithm.h>

WalkableNode::WalkableNode(const Vec2f& _position)
:PathNode(_position)
{
    //ctor
}

WalkableNode::~WalkableNode()
{
    //dtor
}

void WalkableNode::path(PathfindingAlgorithm* algorithm, float distanceTravelled, NodeReference me)
{
    algorithm->add(right,distanceTravelled+1.0f,me,AIManager::eWalkRight);
    algorithm->add(left,distanceTravelled+1.0f,me,AIManager::eWalkLeft);
}

void WalkableNode::setNeighbours(NodeReference _left, NodeReference _right)
{
    left = _left;
    right = _right;
}
