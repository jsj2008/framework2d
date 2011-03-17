#include "DeadEndNode.h"
#include <AI/Paths/PathfindingAlgorithm.h>

DeadEndNode::DeadEndNode(const Vec2f& _position)
:PathNode(_position)
{
    //ctor
}

DeadEndNode::~DeadEndNode()
{
    //dtor
}

void DeadEndNode::path(PathfindingAlgorithm* algorithm, float distanceTravelled, NodeReference me)
{
    algorithm->add(previous,distanceTravelled+1.0f,me,AIManager::eWalkRight);
}

void DeadEndNode::setNeighbour(NodeReference _previous, AIManager::Operation _operation)
{
    previous = _previous;
    operation = _operation;
}
