#ifndef DEADENDNODE_H
#define DEADENDNODE_H

#include <AI/Pathfinding/PathNode.h>
#include <AI/AIManager.h>

class DeadEndNode : public PathNode
{
    public:
        DeadEndNode(const Vec2f& _position);
        virtual ~DeadEndNode();
        void path(PathfindingAlgorithm* algorithm, float distanceTravelled, NodeReference me);
        void setNeighbour(NodeReference _previous, AIManager::Operation _operation);
    protected:
    private:
        NodeReference previous;
        AIManager::Operation operation;
};

#endif // DEADENDNODE_H
