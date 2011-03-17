#include "Paths.h"
#include <AI/Pathfinding/PathNode.h>
#include <Types/Vec2f.h>
#include <AI/Pathfinding/PathfindingAlgorithm.h>

Paths::Paths(std::vector<std::vector<PathNode*>*>& _nodes)
{
    //ctor
    nodes = _nodes;
}

Paths::~Paths()
{
    //dtor
}

Node Paths::findClosestNode(const Vec2f& position)
{
    float shortestDistance = 1000.0f;
    Node closestNode(NULL,0);
    for (auto i = nodes.begin(); i != nodes.end(); i++)
    {
        for (auto ii = (*i)->begin(); ii != (*i)->end(); ii++)
        {
            Vec2f direction = (*ii)->getPosition() - position;
            float lengthSquared = direction.LengthSquared();
            if (lengthSquared < shortestDistance)
            {
                shortestDistance = lengthSquared;
                closestNode = Node(ii - (*i)->begin(), i - nodes.begin());
            }
        }
    }
    return closestNode;
}

void Paths::path(Node start, Node end, std::stack<AIManager::PathInstruction>& instructions)
{
    if (start.set != end.set)
    {
        return;
    }
    auto set = nodes[start.set];
    PathfindingAlgorithm algorithm(*set,start.node,end.node,start.set);
    algorithm.path(instructions);
}
