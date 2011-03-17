#include "PathfindingAlgorithm.h"
#include <AI/Pathfinding/PathNode.h>
#include <cstring>

PathfindingAlgorithm::PathfindingAlgorithm(std::vector<PathNode*>& _nodes, NodeReference _start, NodeReference _target, unsigned int _set)
:nodes(_nodes)
{
    //ctor
    doublesValues = new DoublesValue[nodes.size()];
    target = _target;
    start = _start;
    set = _set;
    add(start, 0.0f, nodes.size(),AIManager::eStandStill);
}
PathfindingAlgorithm::~PathfindingAlgorithm()
{
    //dtor
    delete[] doublesValues;
}
#include <iostream>
void PathfindingAlgorithm::path(std::stack<AIManager::PathInstruction>& instructions)
{
    unsigned int iterations = 0;
    while (workingSet.top().getNode() != target && !workingSet.empty())
    {
        iterations++;
        WorkingSetNode current = workingSet.top();
        workingSet.pop();
        nodes[current.getNode()]->path(this, current.getDistanceTravelled(),current.getNode());
    }
    if (workingSet.top().getNode() == target)
    {
        std::cout << "Found him in " << iterations << " iterations and a distance of " << workingSet.top().getDistanceTravelled() << std::endl;
        std::queue<NodeReference> backTrace;
        NodeReference current = workingSet.top().getNode();
        while (current != start)
        {
            backTrace.push(current);
            AIManager::PathInstruction instruction;
            instruction.node.node = current;
            instruction.node.set = set;
            instruction.operation = doublesValues[current].operation;
            instruction.target = nodes[current]->getPosition();
            instructions.push(instruction);
            current = doublesValues[current].previous;
        }
    }
}

void PathfindingAlgorithm::add(NodeReference node, float distanceTravelled, NodeReference previous, const AIManager::Operation& operation)
{
    if (doublesValues[node].isChecked == true)
    {
        if (distanceTravelled < doublesValues[node].distanceTravelled)
        {
            doublesValues[node].distanceTravelled = distanceTravelled;
            doublesValues[node].previous = previous;
            doublesValues[node].operation = operation;
            workingSet.push(WorkingSetNode(node,distanceTravelled));
        }
    }
    else
    {
        doublesValues[node].isChecked = true;
        doublesValues[node].distanceTravelled = distanceTravelled;
        doublesValues[node].previous = previous;
        doublesValues[node].operation = operation;
        workingSet.push(WorkingSetNode(node,distanceTravelled));
    }
}
